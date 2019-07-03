#pragma once

#include <cstdint>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <ultrainio/chain/callback.hpp>
#include <ultrainio/chain/transaction_metadata.hpp>
#include <ultrainio/chain/types.hpp>

#include <core/Message.h>
#include <core/types.h>
#include <core/BlsVoterSet.h>
#include <boost/asio/steady_timer.hpp>

#include <rpos/RoundInfo.h>
#include <rpos/VoterSet.h>

namespace ultrainio {

    struct SyncTask {
        uint32_t checkBlock;
        BlsVoterSet bvs;
        fc::sha256 nodeId;
        uint32_t startBlock;
        uint32_t endBlock;
        uint32_t seqNum;

        SyncTask(uint32_t _checkBlock, const BlsVoterSet &_bvs, const fc::sha256 &_nodeId, uint32_t _startBlock, uint32_t _endBlock, uint32_t _seqNum)
                : bvs{_bvs}, nodeId(_nodeId) {
            checkBlock = _checkBlock;
            startBlock = _startBlock;
            endBlock = _endBlock;
            seqNum = _seqNum;
        }
    };

    typedef std::map<chain::block_id_type, VoterSet> echo_msg_buff;

    class LightClientProducer;
    class CommitteeSet;
    class UranusNode;

class Scheduler : public std::enable_shared_from_this<Scheduler> {
    public:
        ~Scheduler();
        Scheduler();

        void reset();

        bool isMinPropose(const ProposeMsg &propose_msg);
        bool isMin2FEcho(int totalVoterWeight, uint32_t phasecnt);
        bool isMinFEcho(const VoterSet& voterSet) const;
        bool isMinFEcho(const VoterSet& voterSet, const echo_msg_buff& msgbuff) const;
        bool isMinEcho(const VoterSet& voterSet) const;
        bool isMinEcho(const VoterSet& voterSet, const echo_msg_buff& msgbuff) const;
        Block produceTentativeBlock();
        bool initProposeMsg(ProposeMsg *propose_msg);

        bool isLaterMsg(const ProposeMsg &propose);

        bool isLaterMsgAndCache(const ProposeMsg &propose, bool &duplicate);

        bool isValid(const ProposeMsg &propose);

        bool isBroadcast(const ProposeMsg &propose);

        bool insert(const EchoMsg &echo);

        bool insert(const ProposeMsg &propose);

        bool handleMessage(const EchoMsg &echo);

        bool handleMessage(const ProposeMsg &propose);

        bool handleMessage(const fc::sha256 &nodeId, const ReqSyncMsg &msg);

        bool handleMessage(const fc::sha256 &nodeId, const ReqBlockNumRangeMsg &msg);

        bool handleMessage(const SyncBlockMsg &msg, bool safe);

        bool handleMessage(const fc::sha256 &nodeId, const SyncStopMsg &msg);

        void resetEcho();

        void processCache(const RoundInfo& roundInfo);

        void produceBlock(const chain::signed_block_ptr &block, bool force_push_whole_block = false);
        void clearTrxQueue();

        void init();

        ultrainio::chain::block_id_type getPreviousBlockhash();

        void moveEchoMsg2AllPhaseMap();

        const Block* getBa0Block();

        Block produceBaxBlock();

        bool isNeedSync();

        bool isChangePhase();

        bool fastHandleMessage(const ProposeMsg &propose);

        bool fastHandleMessage(const EchoMsg &echo);

        void fastProcessCache(const RoundInfo& roundInfo);

        bool findEchoCache(const RoundInfo& roundInfo);

        bool isFastba0(const RoundInfo& roundInfo);

        bool findProposeCache(const RoundInfo& roundInfo);

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

        // is invalid block
        bool isBlank(const BlockIdType& blockId);

        // is block without trxs
        bool isEmpty(const BlockIdType& blockId);

        Block blankBlock();

        Block emptyBlock();

        void setBa0Block(const Block& block);

        void insertAccount(VoterSet &info, const EchoMsg &echo);

        void enableEventRegister(bool v);

        bool setBlsVoterSet(const std::string& bls);

        bool verifyMyBlsSignature(const EchoMsg& echo) const;

    private:

        // This function is time consuming, please cache the result empty block.
        std::shared_ptr<Block> generateEmptyBlock();

        bool isDuplicate(const ProposeMsg& proposeMsg);

        bool updateAndMayResponse(VoterSet &info, const EchoMsg &echo, bool response);

        size_t runPendingTrxs(std::list<chain::transaction_metadata_ptr> *trxs,
                              fc::time_point hard_cpu_deadline, fc::time_point block_time);

        size_t runScheduledTrxs(std::vector<chain::transaction_id_type> &trxs,
                                fc::time_point hard_cpu_deadline,
                                fc::time_point block_time);

        size_t runUnappliedTrxs(std::vector<chain::transaction_metadata_ptr> &trxs,
                                fc::time_point hard_cpu_deadline, fc::time_point block_time);

        void start_memleak_check();

        chain::checksum256_type getCommitteeMroot(uint32_t block_num);

        bool hasMultiSignPropose(const ProposeMsg& propose);

        bool hasMultiVotePropose(const EchoMsg& echo);

        BlsVoterSet toBlsVoterSetAndFindEvil(const VoterSet& voterSet, const CommitteeSet& committeeSet, bool genesisPeriod, int weight) const;

        // echo relative
        bool sameBlockNumButBeforePhase(const EchoMsg& echo) const;

        bool sameBlockNumAndPhase(const EchoMsg& echo) const;

        bool obsolete(const EchoMsg& echo) const;

        bool isLaterMsg(const EchoMsg &echo) const;

        bool processLaterMsg(const EchoMsg &echo);

        bool processBeforeMsg(const EchoMsg &echo);

        bool loopback(const EchoMsg& echo) const;

        bool duplicated(const EchoMsg& echo) const;

        bool isValid(const EchoMsg &echo);

        // data member
        Block m_ba0Block;
        BlockIdType m_ba0VerifiedBlkId = BlockIdType();
        BlockIdType m_ba0FailedBlkId = BlockIdType();
        bool m_voterPreRunBa0InProgress = false;
        int m_currentPreRunBa0TrxIndex = -1;
        int m_initTrxCount = 0;
        std::map<chain::block_id_type, ProposeMsg> m_proposerMsgMap;
        std::map<chain::block_id_type, VoterSet> m_echoMsgMap;
        std::map<AccountName, chain::block_id_type> m_committeeVoteBlock;
        std::map<RoundInfo, std::vector<ProposeMsg>> m_cacheProposeMsgMap;
        std::map<RoundInfo, std::vector<EchoMsg>> m_cacheEchoMsgMap;
        std::map<RoundInfo, echo_msg_buff> m_echoMsgAllPhase;
        const uint32_t m_maxCacheEcho = 200;
        const uint32_t m_maxCachePropose = 100;
        const uint32_t m_maxCommitteeSize = 1000; //This is not strict, just to limit cache size.
        const uint32_t m_maxCachedAllPhaseKeys = 200;
        const uint32_t m_maxSyncClients = 10;
        const uint32_t m_maxPacketsOnce = 80;
        const uint32_t m_maxSyncBlocks = 1000;
        boost::asio::steady_timer::duration m_syncTaskPeriod{std::chrono::seconds{2}};
        std::unique_ptr<boost::asio::steady_timer> m_syncTaskTimer;
        boost::asio::steady_timer::duration m_memleakCheckPeriod{std::chrono::seconds{10}};
        std::unique_ptr<boost::asio::steady_timer> m_memleakCheck;
        std::list<SyncTask> m_syncTaskQueue;
        uint32_t m_fast_timestamp;
        BlsVoterSet m_currentBlsVoterSet;
        std::shared_ptr<LightClientProducer> m_lightClientProducer;
        friend class UranusControllerMonitor;
    };
}
