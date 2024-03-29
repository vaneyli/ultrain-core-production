/**
 *  @file
 *  @copyright defined in ultrain/LICENSE.txt
 */
#pragma once
#include <appbase/application.hpp>
#include <ultrainio/chain_plugin/chain_plugin.hpp>
#include <core/protocol.hpp>

namespace ultrainio {
    using namespace appbase;

    struct connection_status {
        string            peer;
        bool              connecting = false;
        handshake_message last_handshake;
    };

    class net_plugin : public appbase::plugin<net_plugin>
    {
    public:
        net_plugin();
        virtual ~net_plugin();

        APPBASE_PLUGIN_REQUIRES((chain_plugin))
        virtual void set_program_options(options_description& cli, options_description& cfg) override;

        void plugin_initialize(const variables_map& options);
        void plugin_startup();
        void plugin_shutdown();

        void   broadcast(const ProposeMsg& propose);
        void   broadcast(const EchoMsg& echo);
        void   send_block(const fc::sha256 &node_id, const SyncBlockMsg& sync_block);
        bool   send_req_sync(const ReqSyncMsg& reqSyncMsg);
        void   send_block_num_range(const fc::sha256 &node_id, const RspBlockNumRangeMsg& last_block_num);
        void   stop_sync_block();

        string                       connect( const string& endpoint );
        string                       disconnect( const string& endpoint );
        optional<connection_status>  status( const string& endpoint )const;
        vector<connection_status>    connections()const;
        vector<connection_status>    get_connected_connections()const;

        size_t num_peers() const;
    private:
        std::unique_ptr<class net_plugin_impl> my;
    };

}

FC_REFLECT( ultrainio::connection_status, (peer)(connecting)(last_handshake) )
