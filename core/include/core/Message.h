#pragma once

#include <fc/reflect/reflect.hpp>
#include <fc/variant.hpp>
#include <ultrainio/chain/block.hpp>
#include <crypto/Signature.h>
#include <core/types.h>

namespace ultrainio {

    enum BlockHeaderExtKey {
        kPreCheckpointId = 0,
        kNextCommitteeMroot,
        kCommitteeSet,
        kBlsVoterSet
    };

    enum ConsensusPhase {
        kPhaseInit = 0,
        kPhaseBA0,
        kPhaseBA1,
        kPhaseBAX
    };

    struct ReqSyncMsg {
        uint32_t seqNum;
        uint32_t startBlockNum;
        uint32_t endBlockNum;
    };

    struct ReqLastBlockNumMsg {
        uint32_t seqNum;
    };

    struct RspLastBlockNumMsg {
        uint32_t seqNum;
        uint32_t blockNum;
        std::string blockHash;
        std::string prevBlockHash;
    };

    // Keep account & signature in the struct and we will use them soon.
    struct SyncBlockMsg {
        uint32_t seqNum;
        AccountName account;
        std::string signature;
        Block block;
    };

    struct SyncStopMsg {
        uint32_t seqNum;
        AccountName account;
        std::string signature;
    };

    struct ProposeMsg {
        Block block;
    };

    struct CommonEchoMsg {
        BlockIdType blockId;
        ConsensusPhase phase;
        uint32_t    baxCount;
#ifdef CONSENSUS_VRF
        uint32_t    proposerPriority;
#else
        AccountName proposer;
#endif
        void toVariants(fc::variants&) const;

        int fromVariants(const fc::variants&);

        bool operator == (const CommonEchoMsg&) const;
    };

    struct UnsignedEchoMsg : public CommonEchoMsg {
        std::string blsSignature;
        AccountName account;
        uint32_t    timestamp;
#ifdef CONSENSUS_VRF
        std::string proof;
#endif
    };

    struct EchoMsg : public UnsignedEchoMsg {
        std::string signature; // hex string
    };
}

FC_REFLECT( ultrainio::ProposeMsg, (block))

#ifdef CONSENSUS_VRF
FC_REFLECT( ultrainio::CommonEchoMsg, (blockId)(phase)(baxCount)(proposerPriority))
FC_REFLECT_DERIVED( ultrainio::UnsignedEchoMsg, (ultrainio::CommonEchoMsg), (blsSignature)(account)(timestamp)(proof))
#else
FC_REFLECT( ultrainio::CommonEchoMsg, (blockId)(phase)(baxCount)(proposer))
FC_REFLECT_DERIVED( ultrainio::UnsignedEchoMsg, (ultrainio::CommonEchoMsg), (blsSignature)(account)(timestamp))
#endif

FC_REFLECT_DERIVED( ultrainio::EchoMsg, (ultrainio::UnsignedEchoMsg), (signature))
FC_REFLECT( ultrainio::ReqSyncMsg, (seqNum)(startBlockNum)(endBlockNum) )
FC_REFLECT( ultrainio::ReqLastBlockNumMsg, (seqNum))
FC_REFLECT( ultrainio::RspLastBlockNumMsg, (seqNum)(blockNum)(blockHash)(prevBlockHash))
FC_REFLECT( ultrainio::SyncBlockMsg, (seqNum)(block))
FC_REFLECT( ultrainio::SyncStopMsg, (seqNum))
