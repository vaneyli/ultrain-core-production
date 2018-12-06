#include "rpos/Config.h"

namespace ultrainio {
    const int Config::kAverageBlockPerMinutes = 6;

    const int Config::kMaxBaxCount = 20;

    const int Config::kDeadlineCnt = 60;

    const double Config::kProposerStakeNumber = 7.0;

    const double Config::kVoterStakeNumber = 1000.0;

    const int Config::kDesiredProposerNumber = 2;

    const int Config::kDesiredVoterNumber = 100;

    const double Config::kSendEchoThresholdRatio = 0.33;

    const double Config::kNextRoundThresholdRatio = 0.67;

    const double Config::kEmptyBlockThresholdRatio = 0.88;

    const double Config::kEmptyBlock2ThresholdRatio = 0.75;

    int Config::s_maxRoundSeconds = 10;

    int Config::s_maxPhaseSeconds = 5;

    const int Config::MAX_LATER_NUMBER = 3;

    int Config::s_maxTrxMicroSeconds = 3300000;
}

