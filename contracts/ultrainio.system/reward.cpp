#include "ultrainio.system.hpp"

#include <ultrainio.token/ultrainio.token.hpp>
#include <ultrainiolib/system.h>
#include <ultrainiolib/transaction.h>
#include <ultrainiolib/transaction.hpp>
#include <cmath>
namespace ultrainiosystem {
   using namespace ultrainio;
   void system_contract::onblock( block_timestamp timestamp, account_name producer ) {

      require_auth(N(ultrainio));

      ultrainio_assert( _gstate.cur_committee_number >= _gstate.min_committee_member_number,
         "The current number of committees must be greater than the minimum to be eligible for new awards");

      /**
       * At startup the initial producer may not be one that is registered / elected
       * and therefore there may be no producer object for them.
       */
      producers_table _producers(_self, master_chain_name);

      if ( !_gstate.start_block){
         uint32_t i {};
         for(auto itr = _producers.begin(); i <= _gstate.min_committee_member_number && itr != _producers.end(); ++itr, ++i){}
		 if( i > _gstate.min_committee_member_number){
			_gstate.start_block=(uint64_t)head_block_number() + 1;
         }else{
            return;
         }
      }

      auto prod = _producers.find(producer);
      if ( prod != _producers.end() ) {
         _gstate.total_cur_chain_block++;
         _producers.modify( prod, [&](auto& p ) {
               p.total_produce_block++;
         });
         print( "onblock timestamp:", timestamp.abstime, " producer:", name{producer}," produce_block:", prod->total_produce_block, "\n" );
      }

      checkresexpire();
      cleanvotetable();
      checkbulletin();
      schedule();
      distributreward();  //automatically send rewards
   }

   void system_contract::reportblocknumber( name chain_name, uint64_t chain_type, account_name producer, uint64_t number) {
      producers_table _producers(_self, chain_name);
      auto prod = _producers.find(producer);
      if ( prod != _producers.end() ) {
        uint64_t curblockreward = 0;
        chaintypes_table type_tbl(_self, _self);
        auto typeiter = type_tbl.find(chain_type);
        if (typeiter != type_tbl.end()) {
            auto const iter = std::find_if( _gstate.block_reward_vec.begin(), _gstate.block_reward_vec.end(), [&](ultrainio::block_reward const& obj){
                                return obj.consensus_period == typeiter->consensus_period;
                            } );
            if(iter != _gstate.block_reward_vec.end()){
                curblockreward = iter->reward;
            }
        }
         _gstate.total_unpaid_balance += curblockreward;
         _producers.modify( prod, [&](auto& p ) {
               p.unpaid_balance += curblockreward;
               p.total_produce_block += number;
         });
         print( "reportblocknumber number:", number, " producer:", name{producer}, " produce_block:", prod->total_produce_block,"\n" );
      }
   }

   void system_contract::claimrewards() {
      require_auth(_self);
      ultrainio_assert( _gstate.cur_committee_number >= _gstate.min_committee_member_number,
         "The current number of committees must be greater than the minimum to be eligible for new awards");

      uint64_t pay_account = N(utrio.resfee);
      asset resfee_tokens =
          ultrainio::token(N(utrio.token)).get_balance( pay_account,symbol_type(CORE_SYMBOL).name());
      print("\nclaimrewards unpaid_balance:",_gstate.total_unpaid_balance," resfee_tokens:",resfee_tokens.amount,"\n");
      ultrainio_assert( resfee_tokens.amount >= 0,
            "resfee_tokens shouldn't be less than 0" );

      if( resfee_tokens.amount < (int64_t)_gstate.total_unpaid_balance){
         INLINE_ACTION_SENDER(ultrainio::token, issue)( N(utrio.token), {{N(ultrainio),N(active)}},
            {pay_account, asset((int64_t)_gstate.total_unpaid_balance - resfee_tokens.amount), std::string("issue tokens for claimrewards")} );
      }
      std::vector<name> chain_name_vec = get_all_chainname();
      for (auto chain_name : chain_name_vec) {
         producers_table _producers(_self, chain_name);
         for(auto itr = _producers.begin(); itr != _producers.end(); ++itr){
            if( itr->unpaid_balance == 0 )
               continue;
            auto producer_unpaid_balance = (int64_t)floor((double)itr->unpaid_balance * 99 /100);
            print("\nclaimrewards subchainname:",name{chain_name}," producer:",name{itr->owner},
            " reward_account:",name{itr->claim_rewards_account}," unpaid_balance:",itr->unpaid_balance,
            " producer_pay_balance:",producer_unpaid_balance,"\n");
            _producers.modify( itr, [&](auto& p) {
               p.unpaid_balance = 0;
            });
            INLINE_ACTION_SENDER(ultrainio::token, safe_transfer)( N(utrio.token), {pay_account,N(active)},
               { pay_account, itr->claim_rewards_account, asset(producer_unpaid_balance), std::string("producer block pay") } );
         }
      }

      if(_gstate.total_unpaid_balance >= 100){
         int64_t master_pay_fee = (int64_t)floor((double)_gstate.total_unpaid_balance /100) ;
         INLINE_ACTION_SENDER(ultrainio::token, safe_transfer)( N(utrio.token), {pay_account,N(active)},
            { pay_account, N(utrio.fee), asset(master_pay_fee), std::string("master producers block pay") } );
      }

      asset fee_tokens =
          ultrainio::token(N(utrio.token)).get_balance( N(utrio.fee),symbol_type(CORE_SYMBOL).name());
      if(fee_tokens.amount <= 0)
         return;
      producers_table _producers(_self, master_chain_name);
      for(auto itr = _producers.begin(); itr != _producers.end(); ++itr){
         if(itr->total_produce_block == 0 || _gstate.total_cur_chain_block <= 0)
            continue;
         auto producer_unpaid_balance = (int64_t)floor((double)itr->total_produce_block * fee_tokens.amount/_gstate.total_cur_chain_block );
         print("\nclaimrewards master producer:",name{itr->owner}," reward_account:",name{itr->claim_rewards_account}," cur_producer_block:",itr->total_produce_block," producer_pay_balance:",producer_unpaid_balance,"\n");
         INLINE_ACTION_SENDER(ultrainio::token, safe_transfer)( N(utrio.token), {N(utrio.fee),N(active)},
            { N(utrio.fee), itr->claim_rewards_account, asset(producer_unpaid_balance), std::string("producer block pay") } );
      }
      _gstate.total_unpaid_balance = 0;
   }

   void system_contract::distributreward(){
      if(!_gstate.is_master_chain())
         return;
      uint32_t block_height = (uint32_t)head_block_number() + 1;
      uint32_t interval_num = seconds_per_day/block_interval_seconds()/24/12;   //TEST:Send rewards once an hour
      if(block_height < 20 || block_height%interval_num != 0) {
         return;
      }
      //distribute rewards
      ultrainio::transaction rewardtrans;
      rewardtrans.actions.emplace_back(
          permission_level{ _self, N(active) }, _self, NEX(claimrewards), std::make_tuple() );
      rewardtrans.actions[0].authorization.emplace_back(permission_level{ N(ultrainio), N(active)});
      rewardtrans.delay_sec = 1;
      uint128_t trxid = now() + _self + N(claimrewards);
      cancel_deferred(trxid);
      rewardtrans.send( trxid, _self, true );
      print("distributreward currenttime:",current_time()," trxid:",trxid);
   }

   void system_contract::claim_reward_to_account(account_name rewardaccount, asset balance){
      uint64_t pay_account = N(utrio.fee);
      asset fee_tokens =
          ultrainio::token(N(utrio.token)).get_balance( pay_account,symbol_type(CORE_SYMBOL).name());
      print("\nclaim_reward_to_account balance:",balance," fee_tokens:",fee_tokens.amount,"\n");

      if(fee_tokens < balance) {
         INLINE_ACTION_SENDER(ultrainio::token, issue)( N(utrio.token), {{N(ultrainio),N(active)}},
            {pay_account, (balance - fee_tokens), std::string("issue tokens for claim_reward_to_account")} );
      }

      INLINE_ACTION_SENDER(ultrainio::token, safe_transfer)( N(utrio.token), {pay_account,N(active)},
            {pay_account, rewardaccount, balance, std::string("producer block pay") } );
   }
} //namespace ultrainiosystem
