#pragma once

#include <QtGlobal>

class RaceStatistics
{
private:
    quint32                     abs_popularity;             // abs_popularity +=
    quint32                     derivative_popularity;      // += derivative_popularity * dt
    float                       trust_factor;               // significance of all other values
                                                            // Statistics has no infulence on any calculation
                                                            // if trust_factor = 0
public:
    RaceStatistics();
};

