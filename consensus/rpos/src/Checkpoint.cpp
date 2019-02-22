#include <rpos/Checkpoint.h>

namespace ultrainio {
    bool Checkpoint::isCheckpoint(const BlockHeader& blockHeader) {
        ExtensionsType ext = blockHeader.header_extensions;
        for (auto& e : ext) {
            if (std::get<0>(e) == kCommitteeSet) {
                return true;
            }
        }
        return false;
    }

    Checkpoint::Checkpoint(const BlockHeader& blockHeader) : m_blockHeader(blockHeader) {
        ExtensionsType ext = m_blockHeader.header_extensions;
        for (auto& e : ext) {
            BlockHeaderExtKey key = static_cast<BlockHeaderExtKey>(std::get<0>(e));
            if (key == kPreCheckpointId) {
            } else if (key == kCommitteeSet) {
                m_committeeSet = CommitteeSet(std::get<1>(e));
            } else if (key == kExtVoterSet) {
            }
        }
    }
}