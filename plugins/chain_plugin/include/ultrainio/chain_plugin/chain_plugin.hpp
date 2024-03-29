/**
 *  @file
 *  @copyright defined in ultrain/LICENSE.txt
 */
#pragma once
#include <appbase/application.hpp>
#include <ultrainio/chain/asset.hpp>
#include <ultrainio/chain/authority.hpp>
#include <ultrainio/chain/account_object.hpp>
#include <ultrainio/chain/block.hpp>
#include <ultrainio/chain/controller.hpp>
#include <ultrainio/chain/contract_table_objects.hpp>
#include <ultrainio/chain/resource_limits.hpp>
#include <ultrainio/chain/transaction.hpp>
#include <ultrainio/chain/abi_serializer.hpp>
#include <ultrainio/chain/plugin_interface.hpp>
#include <ultrainio/chain/ultrainio_object.hpp>
#include <ultrainio/chain/whiteblacklist_object.hpp>

#include <boost/container/flat_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <fc/static_variant.hpp>

namespace fc { class variant; }

namespace ultrainio {
   using chain::controller;
   using std::unique_ptr;
   using namespace appbase;
   using chain::name;
   using chain::action_name;
   using chain::uint128_t;
   using chain::public_key_type;
   using fc::optional;
   using boost::container::flat_set;
   using chain::asset;
   using chain::authority;
   using chain::account_name;
   using chain::abi_def;
   using chain::abi_serializer;

namespace chain_apis {
struct empty{};

struct permission {
   name              perm_name;
   name              parent;
   authority         required_auth;
};

struct resourcelease {
   name           chain_name;
   uint64_t       lease_num = 0;
   std::string    start_time;
   std::string    end_time;
};

template<typename>
struct resolver_factory;

// see specialization for uint64_t in source file
template<typename Type>
Type convert_to_type(const string& str, const string& desc) {
   try {
      return fc::variant(str).as<Type>();
   } FC_RETHROW_EXCEPTIONS(warn, "Could not convert ${desc} string '${str}' to key type.", ("desc", desc)("str",str) )
}

template<>
uint64_t convert_to_type(const string& str, const string& desc);

uint64_t convert_to_scope( const string& str );

class read_only {
   const controller& db;
   const fc::microseconds abi_serializer_max_time;

public:
   static const string KEYi64;

   read_only(const controller& db, const fc::microseconds& abi_serializer_max_time)
      : db(db), abi_serializer_max_time(abi_serializer_max_time) {}

   using get_chain_info_params = empty;

   struct get_info_results {
      string                  server_version;
      chain::chain_id_type    chain_id;
      uint32_t                head_block_num = 0;
      uint32_t                last_irreversible_block_num = 0;
      chain::block_id_type    last_irreversible_block_id;
      chain::block_id_type    head_block_id;
      fc::time_point          head_block_time;
      account_name            head_block_proposer;

      uint64_t                virtual_block_cpu_limit = 0;
      uint64_t                virtual_block_net_limit = 0;

      uint64_t                block_cpu_limit = 0;
      uint64_t                block_net_limit = 0;
      uint32_t                block_interval_ms;
      //string                  recent_slots;
      //double                  participation_rate = 0;
   };
   get_info_results get_chain_info(const get_chain_info_params&) const;

//   struct producer_info {
//      name                       producer_name;
//   };

   using account_resource_limit = chain::resource_limits::account_resource_limit;

   struct get_account_results {
      name                       account_name;
      uint32_t                   head_block_num = 0;
      fc::time_point             head_block_time;

      bool                       privileged = false;
      bool                       updateable;
      fc::time_point             last_code_update;
      fc::time_point             created;

      optional<asset>            core_liquid_balance;

      int64_t                    ram_quota  = 0;
      int64_t                    net_weight = 0;
      int64_t                    cpu_weight = 0;

      account_resource_limit     net_limit;
      account_resource_limit     cpu_limit;
      int64_t                    ram_usage = 0;

      vector<permission>         permissions;

      fc::variant                self_delegated_consensus;
      fc::variant                refund_cons;
      fc::variant                producer_info;
      vector<resourcelease>      chain_resource;
   };

   struct get_account_info_params {
      name account_name;
   };
   get_account_results get_account_info( const get_account_info_params& params )const;

   struct account_exist_result {
      bool is_exist = false;
   };
   struct get_account_exist_params {
      name account_name;
   };
   account_exist_result get_account_exist( const get_account_exist_params& params )const;

   struct trans_fee_result {
      asset fee;
   };
   struct get_trans_fee_params {
      uint64_t block_height;
   };
   trans_fee_result get_trans_fee( const get_trans_fee_params& params )const;

   struct get_contract_results {
      name                   account_name;
      string                 wast;
      string                 wasm;
      fc::sha256             code_hash;
      optional<abi_def>      abi;
   };

   struct get_contract_params {
      name account_name;
      bool code_as_wasm = false;
   };
   struct get_abi_results {
      name                   account_name;
      optional<abi_def>      abi;
   };

   struct get_abi_params {
      name account_name;
   };

   struct get_raw_code_and_abi_results {
      name                   account_name;
      chain::blob            wasm;
      chain::blob            abi;
   };

   struct get_raw_code_and_abi_params {
      name                   account_name;
   };

   get_contract_results get_contract( const get_contract_params& params )const;
   get_abi_results get_abi( const get_abi_params& params )const;
   get_raw_code_and_abi_results get_raw_code_and_abi( const get_raw_code_and_abi_params& params)const;



   struct abi_json2bin_params {
      name         code;
      action_name         action;
      fc::variant  args;
   };
   struct abi_json2bin_result {
      vector<char>   binargs;
   };

   abi_json2bin_result abi_json2bin( const abi_json2bin_params& params )const;


   struct abi_bin2json_params {
      name         code;
      action_name         action;
      vector<char> binargs;
   };
   struct abi_bin2json_result {
      fc::variant    args;
   };

   abi_bin2json_result abi_bin2json( const abi_bin2json_params& params )const;


   struct get_required_keys_params {
      fc::variant transaction;
      flat_set<public_key_type> available_keys;
   };
   struct get_required_keys_result {
      flat_set<public_key_type> required_keys;
   };

   get_required_keys_result get_required_keys( const get_required_keys_params& params)const;

   using get_whiteblacklist_params = empty;

   struct get_whiteblacklist_result {
       flat_set<account_name>         actor_whitelist;
       flat_set<account_name>         actor_blacklist;
       flat_set<account_name>         contract_whitelist;
       flat_set<account_name>         contract_blacklist;
       flat_set<std::pair<account_name, action_name>> action_blacklist;
       flat_set<public_key_type>      key_blacklist;
   };

   get_whiteblacklist_result get_whiteblacklist( const get_whiteblacklist_params& )const;

   struct get_block_info_params {
      string block_num_or_id;
   };

   fc::variant get_block_info(const get_block_info_params& params) const;

   struct get_block_header_state_params {
      string block_num_or_id;
   };

   fc::variant get_block_header_state(const get_block_header_state_params& params) const;
   struct get_table_records_params {
      bool        json = false;
      name        code;
      string      scope;
      name        table;
      string      table_key_type;
      string      table_key;
      string      lower_bound;
      string      upper_bound;
      uint32_t    limit = 10;
      string      key_type;  // type of key specified by index_position
      string      index_position; // 1 - primary (first), 2 - secondary index (in order defined by multi_index), 3 - third index, etc
    };

   struct get_table_records_result {
      vector<fc::variant> rows; ///< one row per item, either encoded as hex String or JSON object
      bool                more = false; ///< true if last element in data is not the end and sizeof data() < limit
   };

   get_table_records_result get_table_records( const get_table_records_params& params )const;

   struct get_table_by_scope_params {
      name        code; // mandatory
      name        table = 0; // optional, act as filter
      string      lower_bound; // lower bound of scope, optional
      string      upper_bound; // upper bound of scope, optional
      uint32_t    limit = 10;
   };
   struct get_table_by_scope_result_row {
      name        code;
      uint64_t      scope;
      name        table;
      name        payer;
      uint32_t    count;
   };
   struct get_table_by_scope_result {
      vector<get_table_by_scope_result_row> rows;
      uint64_t      more; ///< fill lower_bound with this value to fetch more rows
   };

   get_table_by_scope_result get_table_by_scope( const get_table_by_scope_params& params )const;

   struct get_currency_balance_params {
      name             code;
      name             account;
      optional<string> symbol;
   };

   vector<asset> get_currency_balance( const get_currency_balance_params& params )const;

   struct get_currency_stats_params {
      name           code;
      string         symbol;
   };


   struct get_currency_stats_result {
      asset          supply;
      asset          max_supply;
      account_name   issuer;
   };

   fc::variant get_currency_stats( const get_currency_stats_params& params )const;

   struct get_subchain_committee_params {
      name         chain_name;
   };

   struct get_subchain_committee_result {
      std::string     owner;
      std::string     miner_pk;
      std::string     bls_pk;
   };

   vector<get_subchain_committee_result> get_subchain_committee(const get_subchain_committee_params& p) const;

   using get_subchain_resource_params = get_subchain_committee_params;
   std::vector<ultrainio::chain::resources_lease> get_subchain_resource(const get_subchain_resource_params& p) const;

   using get_subchain_block_num_params = get_subchain_committee_params;

   struct block_num_and_id {
       uint32_t       number;
       std::string    block_id;
   };
   struct get_subchain_block_num_result {
       block_num_and_id               confirmed_block;
       std::vector<block_num_and_id>  forks;
   };
   get_subchain_block_num_result get_subchain_block_num(const get_subchain_block_num_params& p) const;

   struct get_subchain_unconfirmed_header_params {
       name chain_name;
   };

   struct get_subchain_unconfirmed_header_result {
       chain::block_id_type confirmed_block_id;
       std::string next_committee_mroot;
       std::vector<chain::role_base> committee_set;
       std::vector<chain::signed_block_header> unconfirmed_headers;
       std::string genesisPk;
   };

   get_subchain_unconfirmed_header_result get_subchain_unconfirmed_header(const get_subchain_unconfirmed_header_params& p) const;

   using get_master_block_num_params = empty;
   using get_master_block_num_result = get_subchain_block_num_result;

   get_master_block_num_result get_master_block_num(const get_master_block_num_params& p) const;

   struct get_producer_info_params {
       account_name   owner;
   };

   struct get_producer_info_result {
       name          location;
       std::string   chain_id;
       chain::block_timestamp genesis_time;
       uint32_t      quit_before_num;
       std::string   genesis_pk;
   };

   get_producer_info_result get_producer_info(const get_producer_info_params& p) const;

   struct get_random_params {
       uint64_t blocknum = 0; // block number
   };

   struct get_random_result {
       std::string random = "";
   };

   get_random_result get_random(const get_random_params& p) const;

   using get_user_bulletin_params = get_subchain_committee_params;
   struct get_user_bulletin_result {
       std::string     owner;
       std::string     owner_pk;
       std::string     active_pk;
       fc::time_point_sec  issue_date;
       uint64_t        block_height;
       bool            updateable;
   };

   std::vector<get_user_bulletin_result> get_user_bulletin(const get_user_bulletin_params& p) const;

   using get_committee_bulletin_params = get_subchain_committee_params;
   std::vector<chain::committee_bulletin> get_committee_bulletin(const get_committee_bulletin_params& p) const;

   struct get_producers_params {
      bool        json = false;
      string      lower_bound;
      bool        all_chain = false;
      name        chain_name = chain::self_chain_name;
   };

   struct producer_with_location {
      name    chain_name;
      fc::variant prod_detail;

      producer_with_location() {chain_name = chain::self_chain_name;}
      producer_with_location(uint64_t location, fc::variant vt): chain_name(location), prod_detail(vt) {}
   };

   struct get_producers_result {
      vector<producer_with_location> rows; ///< one row per item, either encoded as hex string or JSON object
      string              more; ///< fill lower_bound with this value to fetch more rows
   };

   get_producers_result get_producers( const get_producers_params& params )const;

   struct exten_type {
       uint16_t         key;
       std::string      value;
   };
   typedef std::vector<exten_type>  exten_types;

   // sync with ultrainio.system.hpp
   enum global_state_exten_type_key {
      global_state_key_start = 0,
      update_auth = 1,
      confirm_point_interval = 2,
      sidechain_charge_ratio = 3,
      is_claim_reward = 4,
      free_account_per_res = 5,
      version_number = 6,
   };

   struct get_confirm_point_interval_params {
       int dummy;
   };

   struct get_confirm_point_interval_result {
       int confirm_point_interval = 12;
   };

   get_confirm_point_interval_result get_confirm_point_interval(const get_confirm_point_interval_params& p) const;

   struct get_global_exten_params {
       int index = 0;
   };

   struct get_global_exten_result {
       std::string global_exten_data = "";
   };
   get_global_exten_result get_global_exten_data(const get_global_exten_params& p) const;

   bool is_exec_patch_code( int patch_version_number ) const;
   bool is_genesis_finished()const;
   uint64_t get_worldstate_interval()const;

   struct get_scheduled_transactions_params {
      bool        json = false;
      string      lower_bound;  /// timestamp OR transaction ID
      uint32_t    limit = 50;
   };

   struct get_scheduled_transactions_result {
      fc::variants  transactions;
      string        more; ///< fill lower_bound with this to fetch next set of transactions
   };

   get_scheduled_transactions_result get_scheduled_transactions( const get_scheduled_transactions_params& params ) const;

   struct get_merkle_proof_params {
      uint32_t             block_number;
      chain::digest_type   trx_id;
   };

   struct get_merkle_proof_result {
      vector<chain::digest_type> merkle_proof;
      vector<char>               trx_receipt_bytes;
   };

   get_merkle_proof_result get_merkle_proof(const get_merkle_proof_params& params);

   struct verify_merkle_proof_params {
      vector<chain::digest_type> merkle_proof;
      chain::digest_type         transaction_mroot;
      vector<char>               trx_receipt_bytes;
   };

   struct verify_merkle_proof_result {
      bool is_matched;
   };

   verify_merkle_proof_result verify_merkle_proof(const verify_merkle_proof_params& params);

   static void copy_inline_row(const chain::key_value_object& obj, vector<char>& data) {
      data.resize( obj.value.size() );
      memcpy( data.data(), obj.value.data(), obj.value.size() );
   }

   template<typename Function>
   void walk_key_value_table(const name& code, const name& scope, const name& table, Function f) const
   {
      const auto& d = db.db();
      const auto* t_id = d.find<chain::table_id_object, chain::by_code_scope_table>(boost::make_tuple(code, scope, table));
      if (t_id != nullptr) {
         const auto &idx = d.get_index<chain::key_value_index, chain::by_scope_primary>();
         decltype(t_id->id) next_tid(t_id->id._id + 1);
         auto lower = idx.lower_bound(boost::make_tuple(t_id->id));
         auto upper = idx.lower_bound(boost::make_tuple(next_tid));

         for (auto itr = lower; itr != upper; ++itr) {
            if (!f(*itr)) {
               break;
            }
         }
      }
   }

   static uint64_t get_table_index_name(const read_only::get_table_records_params& p, bool& primary);

   template <typename IndexType, typename SecKeyType, typename ConvFn>
   read_only::get_table_records_result get_table_records_by_seckey( const read_only::get_table_records_params& p, const abi_def& abi, ConvFn conv )const {
      read_only::get_table_records_result result;
      const auto& d = db.db();

      uint64_t scope = convert_to_scope( p.scope );

      abi_serializer abis;
      abis.set_abi(abi, abi_serializer_max_time);
      bool primary = false;
      const uint64_t table_with_index = get_table_index_name(p, primary);
      const auto* t_id = d.find<chain::table_id_object, chain::by_code_scope_table>(boost::make_tuple(p.code, scope, p.table));
      const auto* index_t_id = d.find<chain::table_id_object, chain::by_code_scope_table>(boost::make_tuple(p.code, scope, table_with_index));
      if (t_id != nullptr && index_t_id != nullptr) {
         const auto& secidx = d.get_index<IndexType, chain::by_secondary>();
         decltype(index_t_id->id) low_tid(index_t_id->id._id);
         decltype(index_t_id->id) next_tid(index_t_id->id._id + 1);
         auto lower = secidx.lower_bound(boost::make_tuple(low_tid));
         auto upper = secidx.lower_bound(boost::make_tuple(next_tid));

         if (p.lower_bound.size()) {
            if (p.key_type == "name") {
               name s(p.lower_bound);
               SecKeyType lv = convert_to_type<SecKeyType>( s.to_string(), "lower_bound name" ); // avoids compiler error
               lower = secidx.lower_bound( boost::make_tuple( low_tid, conv( lv )));
            } else {
               SecKeyType lv = convert_to_type<SecKeyType>( p.lower_bound, "lower_bound" );
               lower = secidx.lower_bound( boost::make_tuple( low_tid, conv( lv )));
            }
         }
         if (p.upper_bound.size()) {
            if (p.key_type == "name") {
               name s(p.upper_bound);
               SecKeyType uv = convert_to_type<SecKeyType>( s.to_string(), "upper_bound name" );
               upper = secidx.lower_bound( boost::make_tuple( low_tid, conv( uv )));
            } else {
               SecKeyType uv = convert_to_type<SecKeyType>( p.upper_bound, "upper_bound" );
               upper = secidx.lower_bound( boost::make_tuple( low_tid, conv( uv )));
            }
         }

         vector<char> data;

         auto end = fc::time_point::now() + fc::microseconds(1000 * 10); /// 10ms max time

         unsigned int count = 0;
         auto itr = lower;
         for (; itr != upper; ++itr) {

            const auto* itr2 = d.find<chain::key_value_object, chain::by_scope_primary>(boost::make_tuple(t_id->id, itr->primary_key));
            if (itr2 == nullptr) continue;
            copy_inline_row(*itr2, data);

            if (p.json) {
               result.rows.emplace_back(abis.binary_to_variant(abis.get_table_type(p.table), data, abi_serializer_max_time));
            } else {
               result.rows.emplace_back(fc::variant(data));
            }

            if (++count == p.limit || fc::time_point::now() > end) {
               break;
            }
         }
         if (itr != upper) {
            result.more = true;
         }
      }
      return result;
   }

   template <typename IndexType>
   read_only::get_table_records_result get_table_records_ex( const read_only::get_table_records_params& p, const abi_def& abi )const {
      read_only::get_table_records_result result;
      const auto& d = db.db();

      uint64_t scope = convert_to_scope( p.scope );

      abi_serializer abis;
      abis.set_abi(abi, abi_serializer_max_time);
      const auto* t_id = d.find<chain::table_id_object, chain::by_code_scope_table>(boost::make_tuple(p.code, scope, p.table));
      if (t_id != nullptr) {
         const auto& idx = d.get_index<IndexType, chain::by_scope_primary>();
         if(!p.table_key.empty()){
            uint64_t serch_scope = 0;
            if(p.table_key_type == "uint64")
                serch_scope = stol(p.table_key);
            else
                serch_scope = chain::string_to_name(p.table_key.c_str());
            auto it = idx.find(boost::make_tuple( t_id->id,serch_scope ));
            if ( it != idx.end() ) {
                vector<char> data;
                copy_inline_row(*it, data);
                result.rows.emplace_back(abis.binary_to_variant(abis.get_table_type(p.table), data, abi_serializer_max_time));
            }
            return result;
         }
         decltype(t_id->id) next_tid(t_id->id._id + 1);
         auto lower = idx.lower_bound(boost::make_tuple(t_id->id));
         auto upper = idx.lower_bound(boost::make_tuple(next_tid));

         if (p.lower_bound.size()) {
            if (p.key_type == "name") {
               name s(p.lower_bound);
               lower = idx.lower_bound( boost::make_tuple( t_id->id, s.value ));
            } else {
               auto lv = convert_to_type<typename IndexType::value_type::key_type>( p.lower_bound, "lower_bound" );
               lower = idx.lower_bound( boost::make_tuple( t_id->id, lv ));
            }
         }
         if (p.upper_bound.size()) {
            if (p.key_type == "name") {
               name s(p.upper_bound);
               upper = idx.lower_bound( boost::make_tuple( t_id->id, s.value ));
            } else {
               auto uv = convert_to_type<typename IndexType::value_type::key_type>( p.upper_bound, "upper_bound" );
               upper = idx.lower_bound( boost::make_tuple( t_id->id, uv ));
            }
         }

         vector<char> data;

         auto end = fc::time_point::now() + fc::microseconds(1000 * 10); /// 10ms max time

         unsigned int count = 0;
         auto itr = lower;
         for (; itr != upper; ++itr) {
            copy_inline_row(*itr, data);

            if (p.json) {
               result.rows.emplace_back(abis.binary_to_variant(abis.get_table_type(p.table), data, abi_serializer_max_time));
            } else {
               result.rows.emplace_back(fc::variant(data));
            }

            if (++count == p.limit || fc::time_point::now() > end) {
               break;
            }
         }
         if (itr != upper) {
            result.more = true;
         }
      }
      return result;
   }

   friend struct resolver_factory<read_only>;
};

class read_write {
   controller& db;
   const fc::microseconds abi_serializer_max_time;
public:
   read_write(controller& db, const fc::microseconds& abi_serializer_max_time)
         : db(db), abi_serializer_max_time(abi_serializer_max_time) {}

   using push_block_params = chain::signed_block;
   using push_block_results = empty;
   void push_block(const push_block_params& params, chain::plugin_interface::next_function<push_block_results> next);

   using push_tx_params = fc::variant_object;
   struct push_tx_results {
      chain::transaction_id_type  transaction_id;
      fc::variant                 processed;
   };
   void push_tx(const push_tx_params& params, chain::plugin_interface::next_function<push_tx_results> next);

   using push_txs_params  = vector<push_tx_params>;
   using push_txs_results = vector<push_tx_results>;
   void push_txs(const push_txs_params& params, chain::plugin_interface::next_function<push_txs_results> next);

   struct register_event_params {
      string account;
      string post_url;
   };
   struct register_result {
      string result;
   };
   register_result register_event(const register_event_params& params);

   struct unregister_event_params {
      string account;
      string post_url;
   };
   register_result unregister_event(const unregister_event_params& params);

   friend resolver_factory<read_write>;
};
} // namespace chain_apis

class chain_plugin : public plugin<chain_plugin> {
public:
   APPBASE_PLUGIN_REQUIRES()

   chain_plugin();
   virtual ~chain_plugin();

   virtual void set_program_options(options_description& cli, options_description& cfg) override;

   void plugin_initialize(const variables_map& options);
   void plugin_startup();
   void plugin_shutdown();

   chain_apis::read_only get_read_only_api() const { return chain_apis::read_only(chain(), get_abi_serializer_max_time()); }
   chain_apis::read_write get_read_write_api();

   void accept_block( const chain::signed_block_ptr& block );
   void accept_transaction(const chain::packed_transaction& trx,
                           bool from_network,
                           chain::plugin_interface::next_function<chain::transaction_trace_ptr> next);

   bool block_is_on_preferred_chain(const chain::block_id_type& block_id);

   static bool recover_reversible_blocks( const fc::path& db_dir,
                                          uint32_t cache_size,
                                          optional<fc::path> new_db_dir = optional<fc::path>(),
                                          uint32_t truncate_at_block = 0
                                        );

   static bool import_reversible_blocks( const fc::path& reversible_dir,
                                         uint32_t cache_size,
                                         const fc::path& reversible_blocks_file
                                       );

   static bool export_reversible_blocks( const fc::path& reversible_dir,
                                        const fc::path& reversible_blocks_file
                                       );

   // Only call this in plugin_initialize() to modify controller constructor configuration
   controller::config& chain_config();
   // Only call this after plugin_startup()!
   controller& chain();
   // Only call this after plugin_startup()!
   const controller& chain() const;

   chain::chain_id_type get_chain_id() const;
   fc::microseconds get_abi_serializer_max_time() const;

   void handle_guard_exception(const chain::guard_exception& e) const;
private:
   void log_guard_exception(const chain::guard_exception& e) const;

   unique_ptr<class chain_plugin_impl> my;
};

}

FC_REFLECT( ultrainio::chain_apis::permission, (perm_name)(parent)(required_auth) )
FC_REFLECT( ultrainio::chain_apis::resourcelease, (chain_name)(lease_num)(start_time)(end_time) )
FC_REFLECT(ultrainio::chain_apis::empty, )
FC_REFLECT(ultrainio::chain_apis::read_only::get_info_results,
(server_version)(chain_id)(head_block_num)(last_irreversible_block_num)(last_irreversible_block_id)(head_block_id)(head_block_time)(head_block_proposer)(virtual_block_cpu_limit)(virtual_block_net_limit)(block_cpu_limit)(block_net_limit)(block_interval_ms) )
FC_REFLECT(ultrainio::chain_apis::read_only::get_block_info_params, (block_num_or_id))
FC_REFLECT(ultrainio::chain_apis::read_only::get_block_header_state_params, (block_num_or_id))

FC_REFLECT( ultrainio::chain_apis::read_write::push_tx_results, (transaction_id)(processed) )

FC_REFLECT( ultrainio::chain_apis::read_only::get_table_records_params, (json)(code)(scope)(table)(table_key_type)(table_key)(lower_bound)(upper_bound)(limit)(key_type)(index_position) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_table_records_result, (rows)(more) );

FC_REFLECT( ultrainio::chain_apis::read_only::get_table_by_scope_params, (code)(table)(lower_bound)(upper_bound)(limit) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_table_by_scope_result_row, (code)(scope)(table)(payer)(count));
FC_REFLECT( ultrainio::chain_apis::read_only::get_table_by_scope_result, (rows)(more) );

FC_REFLECT( ultrainio::chain_apis::read_only::get_currency_balance_params, (code)(account)(symbol));
FC_REFLECT( ultrainio::chain_apis::read_only::get_currency_stats_params, (code)(symbol));
FC_REFLECT( ultrainio::chain_apis::read_only::get_currency_stats_result, (supply)(max_supply)(issuer));
FC_REFLECT( ultrainio::chain_apis::read_only::get_subchain_committee_params, (chain_name));
FC_REFLECT( ultrainio::chain_apis::read_only::get_subchain_committee_result, (owner)(miner_pk)(bls_pk) );
FC_REFLECT( ultrainio::chain_apis::read_only::block_num_and_id, (number)(block_id));
FC_REFLECT( ultrainio::chain_apis::read_only::get_subchain_block_num_result, (confirmed_block)(forks));
FC_REFLECT( ultrainio::chain_apis::read_only::get_subchain_unconfirmed_header_params, (chain_name));
FC_REFLECT( ultrainio::chain_apis::read_only::get_subchain_unconfirmed_header_result, (confirmed_block_id)(next_committee_mroot)(committee_set)(unconfirmed_headers)(genesisPk));
FC_REFLECT( ultrainio::chain_apis::read_only::get_producer_info_params, (owner) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_producer_info_result, (location)(chain_id)(genesis_time)(quit_before_num)(genesis_pk) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_user_bulletin_result, (owner)(owner_pk)(active_pk)(issue_date)(block_height)(updateable) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_random_params, (blocknum) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_random_result, (random) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_producers_params, (json)(lower_bound)(all_chain)(chain_name) )
FC_REFLECT( ultrainio::chain_apis::read_only::producer_with_location, (chain_name)(prod_detail))
FC_REFLECT( ultrainio::chain_apis::read_only::get_producers_result, (rows)(more) );
FC_REFLECT( ultrainio::chain_apis::read_only::exten_type, (key)(value) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_confirm_point_interval_params, (dummy) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_confirm_point_interval_result, (confirm_point_interval) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_global_exten_params, (index) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_global_exten_result, (global_exten_data) );

FC_REFLECT(ultrainio::chain_apis::read_only::get_account_results,
        (account_name)(head_block_num)(head_block_time)(privileged)(updateable)(last_code_update)(created)(core_liquid_balance)(ram_quota)(net_weight)(cpu_weight)(
                net_limit)(cpu_limit)(ram_usage)(permissions)(
                self_delegated_consensus)(refund_cons)(producer_info)(chain_resource))
FC_REFLECT(ultrainio::chain_apis::read_only::account_exist_result,(is_exist))
FC_REFLECT( ultrainio::chain_apis::read_only::get_scheduled_transactions_params, (json)(lower_bound)(limit) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_scheduled_transactions_result, (transactions)(more) );
FC_REFLECT( ultrainio::chain_apis::read_only::get_contract_results, (account_name)(code_hash)(wast)(wasm)(abi) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_abi_results, (account_name)(abi) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_account_info_params, (account_name) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_account_exist_params, (account_name) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_trans_fee_params, (block_height) )
FC_REFLECT(ultrainio::chain_apis::read_only::trans_fee_result,(fee))
FC_REFLECT( ultrainio::chain_apis::read_only::get_contract_params, (account_name)(code_as_wasm) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_abi_params, (account_name) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_raw_code_and_abi_params, (account_name) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_raw_code_and_abi_results, (account_name)(wasm)(abi) )
//FC_REFLECT( ultrainio::chain_apis::read_only::producer_info, (producer_name) )
FC_REFLECT( ultrainio::chain_apis::read_only::abi_json2bin_params, (code)(action)(args) )
FC_REFLECT( ultrainio::chain_apis::read_only::abi_json2bin_result, (binargs) )
FC_REFLECT( ultrainio::chain_apis::read_only::abi_bin2json_params, (code)(action)(binargs) )
FC_REFLECT( ultrainio::chain_apis::read_only::abi_bin2json_result, (args) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_required_keys_params, (transaction)(available_keys) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_required_keys_result, (required_keys) )
FC_REFLECT( ultrainio::chain_apis::read_only::get_whiteblacklist_result, (actor_whitelist)(actor_blacklist)(contract_whitelist)(contract_blacklist)(action_blacklist)(key_blacklist) )

FC_REFLECT( ultrainio::chain_apis::read_write::register_event_params, (account)(post_url));
FC_REFLECT( ultrainio::chain_apis::read_write::unregister_event_params, (account)(post_url));
FC_REFLECT( ultrainio::chain_apis::read_write::register_result, (result));

FC_REFLECT( ultrainio::chain_apis::read_only::get_merkle_proof_params, (block_number)(trx_id));
FC_REFLECT( ultrainio::chain_apis::read_only::get_merkle_proof_result, (merkle_proof)(trx_receipt_bytes));
FC_REFLECT( ultrainio::chain_apis::read_only::verify_merkle_proof_params, (merkle_proof)(transaction_mroot)(trx_receipt_bytes));
FC_REFLECT( ultrainio::chain_apis::read_only::verify_merkle_proof_result, (is_matched));
