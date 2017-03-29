#pragma once

#include <cstdint>

class RaceStatistics
{
private:
    uint32_t abs_popularity;            // abs_popularity +=
    int32_t derivative_popularity;      // += derivative_popularity * dt
    float trust_factor;                 // significance of all other values
                                        // Statistics has no infulence on any calculation
                                        // if trust_factor = 0
public:
    RaceStatistics();
};

