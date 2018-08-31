#include "rpos/VoterSystem.h"

#include <limits>

#include <boost/math/distributions/binomial.hpp>

#include <crypto/Ed25519.h>
#include <rpos/Config.h>
#include <rpos/MessageManager.h>
#include <rpos/Node.h>
#include <rpos/Proof.h>

using boost::math::binomial;
using std::string;

namespace ultrainio {
    double VoterSystem::getProposerRatio() {
        long totalStake = getTotalStakes(UranusNode::getInstance()->getBlockNum());
        return Config::PROPOSER_STAKES_NUMBER / totalStake;
    }

    double VoterSystem::getVoterRatio() {
        long totalStake = getTotalStakes(UranusNode::getInstance()->getBlockNum());
        return Config::VOTER_STAKES_NUMBER / totalStake;
    }

    bool VoterSystem::isGenesisPeriod(uint32_t blockNum) const {
        std::shared_ptr<MessageManager> messageManagerPtr = MessageManager::getInstance();
        std::shared_ptr<CommitteeState> committeeStatePtr = messageManagerPtr->getCommitteeStatePtr(
                blockNum);
        //TODO(qinxiaofen) still genesis startup, maybe also compare timestamp
        if (!committeeStatePtr || !(committeeStatePtr->chainStateNormal)) {
            return true;
        }
        return false;
    }

    long VoterSystem::getTotalStakes(uint32_t blockNum) const {
        return getCommitteeMemberNumber(blockNum) * Config::DEFAULT_THRESHOLD;
    }

    int VoterSystem::getStakes(const std::string &pk) {
        std::shared_ptr<UranusNode> nodePtr = UranusNode::getInstance();
        bool isNonProducingNode = nodePtr->getNonProducingNode();
        string myPk(nodePtr->getSignaturePublic());
        // (shenyufeng)always be no listener
        if (isNonProducingNode && pk == myPk)
            return 0;
        if (isCommitteeMember(PublicKey(pk))) {
            return Config::DEFAULT_THRESHOLD;
        }
        return 0;
    }

    int VoterSystem::getCommitteeMemberNumber(uint32_t blockNum) const {
        if (isGenesisPeriod(blockNum)) {
            return 1; // genesis leader only
        }
        std::shared_ptr<MessageManager> messageManagerPtr = MessageManager::getInstance();
        std::shared_ptr<CommitteeState> committeeStatePtr = messageManagerPtr->getCommitteeStatePtr(
                blockNum);
        return committeeStatePtr->cinfo.size();
    }

    bool VoterSystem::isCommitteeMember(const PublicKey& publicKey) const {
        std::shared_ptr<UranusNode> nodePtr = UranusNode::getInstance();
        uint32_t blockNum = nodePtr->getBlockNum();

        if (isGenesisPeriod(blockNum) && nodePtr->isGenesisLeader(publicKey)) {
            return true;
        } else if (!isGenesisPeriod(blockNum) && inCommitteeMemberList(blockNum, publicKey)) {
            return true;
        }
        return false;
    }

    bool VoterSystem::inCommitteeMemberList(uint32_t blockNum, const PublicKey& publicKey) const {
        std::shared_ptr<MessageManager> messageManagerPtr = MessageManager::getInstance();
        std::shared_ptr<CommitteeState> committeeStatePtr = messageManagerPtr->getCommitteeStatePtr(
                blockNum);
        if (committeeStatePtr) {
            for (auto& v : committeeStatePtr->cinfo) {
                if (PublicKey(v.pk) == publicKey) {
                    return true;
                }
            }
        }
        return false;
    }

    std::shared_ptr<CommitteeState> VoterSystem::getCommitteeState() {
        static const auto &ro_api = appbase::app().get_plugin<chain_plugin>().get_read_only_api();
        static struct chain_apis::read_only::get_producers_params params;
        CommitteeInfo cinfo;
        auto statePtr(std::make_shared<CommitteeState>());
        params.json=true;
        params.lower_bound="";
        try {
            auto result = ro_api.get_producers(params, true);
            if(!result.rows.empty()) {
                for( const auto& r : result.rows ) {
                    cinfo.accountName = r["owner"].as_string();
                    cinfo.pk = r["producer_key"].as_string();
                    cinfo.stakesCount = r["total_votes"].as_int64();
                    statePtr->cinfo.push_back(cinfo);
                }
                ilog("#########################there is ${p} committee member enabled", ("p", result.rows.size()));
           }
           if (result.thresh_activated_stake_time > 0 && statePtr->cinfo.size() > Config::MIN_COMMITTEE_MEMBER_NUMBER) {
               statePtr->chainStateNormal = true;
           }
        }
        catch(...) {
            ilog("catch expe");
            return nullptr;
        }
        return statePtr;
    }

    int VoterSystem::count(const Proof& proof, int stakes, double p) {
        double rand = proof.getRand();
        return reverseBinoCdf(rand, stakes, p);
    }

    int VoterSystem::reverseBinoCdf(double rand, int stake, double p) {
        int k = 0;
        binomial b(stake, p);

        while (rand > boost::math::cdf(b, k)) {
            k++;
        }
        return k;
    }
}
