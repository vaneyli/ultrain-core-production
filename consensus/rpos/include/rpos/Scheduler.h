#pragma once

#include <cstdint>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <ultrainio/chain/transaction_metadata.hpp>
#include <ultrainio/chain/types.hpp>

#include <core/Message.h>
#include <core/Redefined.h>
#include <boost/asio/steady_timer.hpp>

namespace ultrainio {
    class UranusNode;

    struct echo_message_info {
        EchoMsg echo;
        std::vector<AccountName> accountPool;
        std::vector<std::string> proofPool;
        std::vector<std::string> sigPool;
        std::vector<uint32_t>    timePool;
        int totalVoter;
        bool hasSend;

        echo_message_info() :
                echo(), accountPool(), proofPool(), sigPool(), timePool(), totalVoter(0), hasSend(false) {}

        bool empty() {
            if (accountPool.size() <= 0) {
                return true;
            }
            return false;
        }
    };

    struct msgkey {
        uint32_t blockNum;
        uint16_t phase;

        bool operator<(const msgkey &other) const {
            if (blockNum < other.blockNum) {
                return true;
            } else if (blockNum == other.blockNum) {
                return phase < other.phase;
            }
            return false;
        }
    };

    struct SyncTask {
        std::string peerAddr;
        uint32_t startBlock;
        uint32_t endBlock;
        uint32_t seqNum;

        SyncTask(const std::string &_peerAddr, uint32_t _startBlock, uint32_t _endBlock, uint32_t _seqNum) : peerAddr(_peerAddr) {
            startBlock = _startBlock;
            endBlock = _endBlock;
            seqNum = _seqNum;
        }
    };

    typedef std::map<chain::block_id_type, echo_message_info> echo_msg_buff;

    class Scheduler : public std::enable_shared_from_this<Scheduler> {
    public:
        Scheduler();

        void reset();

        bool isMinPropose(const ProposeMsg &propose_msg);
        bool isMin2FEcho(int totalVoter, uint32_t phasecnt);
        bool isMinFEcho(const echo_message_info &info);
        bool isMinFEcho(const echo_message_info &info, const echo_msg_buff &msgbuff);
        bool isMinEcho(const echo_message_info &info);
        bool isMinEcho(const echo_message_info &info, const echo_msg_buff &msgbuff);
        Block produceTentativeBlock();
        bool isProcessNow();
        bool initProposeMsg(ProposeMsg *propose_msg);

        bool isLaterMsg(const EchoMsg &echo);

        bool isLaterMsg(const ProposeMsg &propose);

        bool isLaterMsgAndCache(const EchoMsg &echo, bool &duplicate);

        bool isLaterMsgAndCache(const ProposeMsg &propose, bool &duplicate);

        bool isValid(const EchoMsg &echo);

        bool isValid(const ProposeMsg &propose);

        bool isBroadcast(const EchoMsg &echo);

        bool isBroadcast(const ProposeMsg &propose);

        bool insert(const EchoMsg &echo);

        bool insert(const ProposeMsg &propose);

        bool handleMessage(const EchoMsg &echo);

        bool handleMessage(const ProposeMsg &propose);

        bool handleMessage(const std::string &peer_addr, const ReqSyncMsg &msg);

        bool handleMessage(const std::string &peer_addr, const ReqLastBlockNumMsg &msg);

        bool handleMessage(const Block &msg);

        bool handleMessage(const std::string &peer_addr, const SyncStopMsg &msg);

        void resetEcho();

        void processCache(const msgkey &msg_key);

        void produceBlock(const chain::signed_block_ptr &block, bool force_push_whole_block = false);
        void clearTrxQueue();

        void init();

        ultrainio::chain::block_id_type getPreviousBlockhash();

        void moveEchoMsg2AllPhaseMap();

        const Block* getBa0Block();

        Block produceBaxBlock();

        bool isBeforeMsg(const EchoMsg &echo);

        bool processBeforeMsg(const EchoMsg &echo);

        bool isBeforeMsgAndProcess(const EchoMsg &echo);

        uint32_t isSyncing();

        bool isChangePhase();

        bool fastHandleMessage(const ProposeMsg &propose);

        bool fastHandleMessage(const EchoMsg &echo);

        void fastProcessCache(const msgkey &msg_key);

        bool findEchoCache(const msgkey &msg_key);

        bool findProposeCache(const msgkey &msg_key);

        uint32_t getLastBlocknum();

        void startSyncTaskTimer();

        void processSyncTask();

        template<class T>
        void clearMsgCache(T &cache, uint32_t blockNum);

        bool preRunBa0BlockStart();

        bool preRunBa0BlockStep();

        bool verifyBa0Block();

        void clearPreRunStatus();

        uint32_t getFastTimestamp();

        void resetTimestamp();

        void clearOldCachedProposeMsg();

        void clearOldCachedEchoMsg();

        bool isBlank(const BlockIdType& blockId);

        bool isEmpty(const BlockIdType& blockId);

        Block blankBlock();

        Block emptyBlock();

        void setBa0Block(const Block& block);

        std::shared_ptr<AggEchoMsg> generateAggEchoMsg(std::shared_ptr<Block> blockPtr);

        void insertAccount(echo_message_info &info, const EchoMsg &echo);

        void enableEventRegister(bool v);
    private:
        // This function is time consuming, please cache the result empty block.
        std::shared_ptr<Block> generateEmptyBlock();

        bool isDuplicate(const ProposeMsg& proposeMsg);

        bool updateAndMayResponse(echo_message_info &info, const EchoMsg &echo, bool response);

        size_t runPendingTrxs(std::list<chain::transaction_metadata_ptr> *trxs,
                              fc::time_point hard_cpu_deadline, fc::time_point block_time);

        size_t runScheduledTrxs(const std::vector<chain::transaction_id_type> &trxs,
                                fc::time_point hard_cpu_deadline,
                                fc::time_point block_time);

        size_t runUnappliedTrxs(const std::vector<chain::transaction_metadata_ptr> &trxs,
                                fc::time_point hard_cpu_deadline, fc::time_point block_time);

        echo_message_info findEchoMsg(BlockIdType blockId);

        void start_memleak_check();

        // data member
        Block m_ba0Block;
        BlockIdType m_ba0VerifiedBlkId = BlockIdType();
        bool m_voterPreRunBa0InProgress = false;
        int m_currentPreRunBa0TrxIndex = -1;
        int m_initTrxCount = 0;
        std::map<chain::block_id_type, ProposeMsg> m_proposerMsgMap;
        std::map<chain::block_id_type, echo_message_info> m_echoMsgMap;
        std::map<msgkey, std::vector<ProposeMsg>> m_cacheProposeMsgMap;
        std::map<msgkey, std::vector<EchoMsg>> m_cacheEchoMsgMap;
        std::map<msgkey, echo_msg_buff> m_echoMsgAllPhase;
        const uint32_t m_maxCacheEcho = 60;
        const uint32_t m_maxCachePropose = 120;
        const uint32_t m_maxCommitteeSize = 1000; //This is not strict, just to limit cache size.
        const uint32_t m_maxCachedAllPhaseKeys = 200;
        const uint32_t m_maxSyncClients = 10;
        const uint32_t m_maxPacketsOnce = 80;
        boost::asio::steady_timer::duration m_syncTaskPeriod{std::chrono::seconds{1}};
        std::unique_ptr<boost::asio::steady_timer> m_syncTaskTimer;
        boost::asio::steady_timer::duration m_memleakCheckPeriod{std::chrono::seconds{10}};
        std::unique_ptr<boost::asio::steady_timer> m_memleakCheck;
        std::list<SyncTask> m_syncTaskQueue;
        uint32_t m_fast_timestamp;
        friend class UranusControllerMonitor;
    };
}