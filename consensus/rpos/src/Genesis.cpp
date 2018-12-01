#include "rpos/Genesis.h"

#include <rpos/Config.h>

namespace ultrainio {
    const std::string Genesis::kGenesisAccount("genesis");

    boost::chrono::system_clock::time_point Genesis::s_time;

    int Genesis::s_genesisStartupTime = 60;

    int Genesis::s_genesisStartupBlockNum = 60 * Config::kAverageBlockPerMinutes;

    // set in config.ini for single test net
    std::string Genesis::s_genesisPk("369c31f242bfc5093815511e4a4eda297f4b8772a7ff98f7806ce7a80ffffb35");
}