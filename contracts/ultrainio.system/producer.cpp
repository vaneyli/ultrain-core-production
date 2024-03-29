/**
 *  @file
 *  @copyright defined in ultrain/LICENSE.txt
 */
#include "ultrainio.system.hpp"

#include <ultrainiolib/crypto.h>
#include <ultrainiolib/datastream.hpp>
#include <ultrainiolib/serialize.hpp>
#include <ultrainiolib/transaction.hpp>
#include <ultrainio.token/ultrainio.token.hpp>

#include <algorithm>
#include <cmath>

namespace ultrainiosystem {
    using namespace ultrainio;

    void system_contract::regproducer(const account_name producer,
                                      const std::string& producer_key,
                                      const std::string& bls_key,
                                      account_name rewards_account,
                                      const std::string& url,
                                      name location ) {
        require_auth(_self);
        ultrainio_assert( url.size() < 512, "url too long" );
        // key is hex encoded
        ultrainio_assert( producer_key.size() == 64, "public key should be of size 64" );
        ultrainio_assert( bls_key.size() == 130, "public bls key should be of size 130" );
        ultrainio_assert( is_account( producer ), "producer account not exists" );
        ultrainio_assert( is_account( rewards_account ), "rewards account not exists" );
        check_producer_evillist( producer );
        if(location != self_chain_name) {
            ultrainio_assert(location != N(master) && location != default_chain_name, "wrong location name");
            ultrainio_assert(_chains.find(location) != _chains.end(),
                                 "wrong location, chain is not existed");
        }
        uint64_t curblocknum = (uint64_t)head_block_number() + 1;
        auto briefprod = _briefproducers.find(producer);
        if(briefprod == _briefproducers.end()) {
            //new producer, add to disabled table for now
            disabled_producers_table dp_tbl(_self, _self);
            dp_tbl.emplace( [&]( disabled_producer& dis_prod ) {
                dis_prod.owner                   = producer;
                dis_prod.producer_key            = producer_key;
                dis_prod.bls_key                 = bls_key;
                dis_prod.url                     = url;
                dis_prod.last_operate_blocknum   = curblocknum;
                dis_prod.delegated_cons_blocknum = 0;
                dis_prod.claim_rewards_account   = rewards_account;
            });
            _briefproducers.emplace([&]( producer_brief& brief_prod ) {
                brief_prod.owner        = producer;
                brief_prod.location     = location;
                brief_prod.in_disable   = true;
            });
        } else {
            ultrainio_assert( briefprod->in_disable, "producer already exist" );
            if(location == default_chain_name) {
                location = briefprod->location;
            }
            disabled_producers_table dp_tbl(_self, _self);
            auto it_disable = dp_tbl.find(producer);
            ultrainio_assert(it_disable != dp_tbl.end(), "error: producer is not in disabled table");
            ultrainio_assert(it_disable->last_operate_blocknum < curblocknum, "only one action can be performed in a block");
            dp_tbl.modify(it_disable, [&]( disabled_producer& dis_prod ) {
               dis_prod.producer_key            = producer_key;
               dis_prod.bls_key                 = bls_key;
               dis_prod.url                     = url;
               dis_prod.last_operate_blocknum   = curblocknum;
               dis_prod.claim_rewards_account   = rewards_account;
            });
        }

        /*
        if ( !is_has_ultrainio_auth ) {
            ultrainio_assert( _gstate.is_master_chain(), "only master chain allow regproducer" );
            asset cur_tokens =
                ultrainio::token(N(utrio.token)).get_balance( producer,symbol_type(CORE_SYMBOL).name());
            ultrainio_assert( cur_tokens.amount >= 50000,
                              "The current action fee is 5 UGAS, please ensure that the account is fully funded" );
            INLINE_ACTION_SENDER(ultrainio::token, safe_transfer)( N(utrio.token), {producer,N(active)},
                { producer, N(utrio.fee), asset(50000), std::string("regproducer fee") } );
            for(auto ite_chain = _chains.begin(); ite_chain != _chains.end(); ++ite_chain) {
                if(ite_chain->chain_name == N(master))
                    continue;
                if(is_empowered(producer, ite_chain->chain_name))
                    continue;
                std::string errorlog = std::string("producer account must be synchronized to all the subchains, \
                        so that we can schedule and secure the subchains. Please perform empoweruser action \
                        producer:") + name{producer}.to_string() + std::string(" not synchronized to subchain:") + name{ite_chain->chain_name}.to_string();
                ultrainio_assert( false, errorlog.c_str());
            }
        }*/
    }

    std::vector<name> system_contract::get_all_chainname() {
        std::vector<name> scopes;
        for(auto ite_chain = _chains.begin(); ite_chain != _chains.end(); ++ite_chain) {
            if(ite_chain->chain_name == N(master))
                continue;
            scopes.emplace_back(ite_chain->chain_name);
        }
        return scopes;
    }

    void system_contract::moveprod(account_name producer, const std::string&  producerkey, const std::string& blskey,
                                   bool from_disable, name from_chain, bool to_disable, name to_chain) {
        require_auth(_self);
        if(from_disable && to_disable) {
            ultrainio_assert(false, "error: cannot move a producer from disable to disable");
        } else if (!from_disable && !to_disable) {
            ultrainio_assert(_gstate.is_master_chain(), "move producer between chains can only be performed on master chain");
        }

        auto briefprod = _briefproducers.find(producer);
        ultrainio_assert(briefprod != _briefproducers.end(), "not a producer");

        auto current_block_number = uint64_t(head_block_number() + 1);
        producer_info prod_info;
        if(from_disable) {
            disabled_producers_table dp_tbl(_self, _self);
            auto it_disable = dp_tbl.find(producer);
            ultrainio_assert(it_disable != dp_tbl.end(), "error: producer is not in disabled table");
            prod_info = producer_info(*it_disable, 0, 0, 0);
            dp_tbl.erase(it_disable);

            print("move producer ", name{producer}, " from disable");
        } else {
            producers_table _producers(_self, from_chain);
            auto producer_iter = _producers.find(producer);
            ultrainio_assert(producer_iter != _producers.end(), "error: producer to move out is not found in its location");
            prod_info = *producer_iter;
            remove_from_chain(from_chain, producer, current_block_number);
            print("move producer ", name{producer}, " from ", from_chain);
            cmtbulletin  cb_tbl(_self, from_chain);
            auto record = cb_tbl.find(current_block_number);
            if(record == cb_tbl.end()) {
                cb_tbl.emplace([&](auto& new_change) {
                    new_change.block_num = current_block_number;
                    new_change.change_type = remove_producer;
                });
            } else if ((record->change_type & remove_producer) == 0) {
                cb_tbl.modify(record, [&](auto& _change) {
                    _change.change_type |= remove_producer;
                });
            }
        }

        if(to_disable) {
            disabled_producers_table dp_tbl(_self, _self);
            dp_tbl.emplace( [&]( disabled_producer& dis_prod ) {
                dis_prod = prod_info;
                dis_prod.delegated_cons_blocknum = current_block_number;
            });
            record_rewards_for_disproducer( prod_info.owner, prod_info.claim_rewards_account, prod_info.unpaid_balance );
            _briefproducers.modify(briefprod, [&](producer_brief& producer_brf) {
                producer_brf.in_disable = true;
            });
            print(" to disable");
        } else {
            ultrainio_assert( producerkey == prod_info.producer_key, "error: public producer key not consistent with the original chain" );
            ultrainio_assert( blskey == prod_info.bls_key, "error: public bls key not consistent with the original chain" );
            prod_info.unpaid_balance = remove_rewards_for_enableproducer( prod_info.owner );
            remove_producer_from_evillist( producer );  //Will be moved to enabled producer, should be removed from the evil list
            add_to_chain(to_chain, prod_info, current_block_number);
            _briefproducers.modify(briefprod, [&](producer_brief& producer_brf) {
                producer_brf.in_disable = false;
                producer_brf.location = to_chain;
            });
            print(" to ", to_chain, "\n");
            cmtbulletin  cb_tbl(_self, to_chain);
            auto record = cb_tbl.find(current_block_number);
            if(record == cb_tbl.end()) {
                cb_tbl.emplace([&](auto& new_change) {
                    new_change.block_num = current_block_number;
                    new_change.change_type = add_producer;
                });
            } else if ((record->change_type & add_producer) == 0) {
                cb_tbl.modify(record, [&](auto& _change) {
                    _change.change_type |= add_producer;
                });
            }
        }
    }

   /*
   verifyprodevil function manually parses input data (instead of taking parsed arguments from dispatcher)
   because parsing data in the dispatcher uses too much CPU in case if evil_info is big

   If we use dispatcher the function signature should be:

   void system_contract::verifyprodevil( account_name producer, const std::string& evil_info )
   */
   void system_contract::verifyprodevil() {
      require_auth( _self );
      constexpr size_t max_stack_buffer_size = 512;
      size_t size = action_data_size();
      char* buffer = (char*)( max_stack_buffer_size < size ? malloc(size) : alloca(size) );
      read_action_data( buffer, size );
      account_name producer;
      std::string evil_info;

      datastream<const char*> ds( buffer, size );
      ds >> producer >> evil_info;

      //TODO  verify producer evil

      uint128_t sendid = N(evilprod) + producer;
      cancel_deferred(sendid);
      ultrainio::transaction out;
      out.actions.emplace_back( permission_level{ _self, N(active) }
                              , _self
                              , NEX(procevilprod)
                              , std::make_tuple(producer, producer_evil_type::radio_error_echo_msg)
                              );
      out.delay_sec = 0;
      out.send( sendid, _self, true );
   }

   void system_contract::procevilprod( account_name producer, uint16_t evil_type ) {
      require_auth( _self );
      auto briefprod = _briefproducers.find( producer );
      ultrainio_assert( briefprod != _briefproducers.end(), "not a producer" );
      ultrainio_assert( !briefprod->in_disable, "producer in disabled" );
      producers_table _producers(_self, briefprod->location);
      const auto& it = _producers.find( producer );
      ultrainio_assert(it != _producers.end(), "producer is not found in its location");
      if( _gstate.is_master_chain() ) {
         evilprodtab evilprod( _self, _self );
         auto evilprod_itr = evilprod.find( producer );
         if( evilprod_itr == evilprod.end() ) {
            evilprod.emplace([&](auto& e) {
               e.owner = producer;
               e.evil_type = evil_type;
               if( producer_evil_type::radio_error_echo_msg == evil_type ){  //Freeze delegate tokens
                  e.is_freeze = true;
               }
            });
         } else {
            evilprod.modify(evilprod_itr, [&]( auto& e ) {
               e.evil_type = evil_type;
               if( producer_evil_type::radio_error_echo_msg == evil_type ){  //Freeze delegate tokens
                  e.is_freeze = true;
               }
            });
         }

         //remove committee
         moveprod_param mv_prod(it->owner, it->producer_key, it->bls_key, false, briefprod->location, true, name{N(disable)});
         send_defer_moveprod_action( mv_prod );
      } else {  //sidechain record bulletin
         ultrainio_assert( producer_evil_type::radio_error_echo_msg == evil_type
                           , " Non specified evil msg cannot emplace sidechain bulletin board" );
         bulletintab  bltn( _self, N(master) );
         auto current_block_number = uint64_t(head_block_number() + 1);
         auto bltn_itr = bltn.find(current_block_number);
         ultrainio_assert( bltn_itr == bltn.end(), " evil bulletin current blockheight already exist" );
         bltn.emplace([&](auto& b) {
            b.block_num = current_block_number;
            b.action_name.insert("procevilprod");
         });
      }
   }

   void system_contract::send_defer_moveprod_action( const moveprod_param& prodparam ) const {
      uint128_t sendid = N(moveprod) + prodparam.producer;
      cancel_deferred(sendid);
      ultrainio::transaction out;
      out.actions.emplace_back( permission_level{ _self, N(active) }, _self, NEX(moveprod), prodparam );
      out.delay_sec = 0;
      out.send( sendid, _self, true );
   }

   void system_contract::check_producer_evillist( const account_name& producer ) const {
      evilprodtab evilprod( _self, _self );
      auto evilprod_itr = evilprod.find( producer );
      if( evilprod_itr == evilprod.end() ) {
         return;
      }
      //freeze not allowed to be producer again
      ultrainio_assert( !evilprod_itr->is_freeze, " evil producer not allowed to be producer again" );
   }

   void system_contract::remove_producer_from_evillist( const account_name& producer ) const {
      evilprodtab evilprod( _self, _self );
      auto evilprod_itr = evilprod.find( producer );
      if( evilprod_itr != evilprod.end() ) {
         evilprod.erase( evilprod_itr );
      }
   }

   void system_contract::check_producer_lastblock( const name& chain_name, uint64_t block_height ) const {
      if( !_gstate.is_master_chain() ) {
         return;
      }
      uint64_t produce_critical_number = 3 * seconds_per_day / block_interval_seconds();
      uint32_t interval_num = seconds_per_day/block_interval_seconds() + 3;   // check_producer_lastblock once about an day
      if(block_height < produce_critical_number || block_height%interval_num != 0) {
         return;
      }
      auto last_allow_produce_block = block_height - produce_critical_number;
      producers_table _producers(_self, chain_name);
      for(auto itr = _producers.begin(); itr != _producers.end(); ++itr){
         if( itr->last_record_blockheight > last_allow_produce_block ){
            continue;
         }
         uint128_t sendid = N(procevilprod) + itr->owner;
         cancel_deferred(sendid);
         ultrainio::transaction out;
         out.actions.emplace_back( permission_level{ _self, N(active) }
                                 , _self
                                 , NEX(procevilprod)
                                 , std::make_tuple(itr->owner, producer_evil_type::limit_time_not_produce)
                                 );
         out.delay_sec = 1;
         out.send( sendid, _self, true );
      }
   }

} /// namespace ultrainiosystem
