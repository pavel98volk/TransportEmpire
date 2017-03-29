#pragma once

#include <cstdint>

class RouteStatistics
{
private:
    float quality_factor;                   // statistical modeling factor
    uint32_t population_coverage;           // a sum of all cities population   (TOBE reworked)
    uint32_t square_coverage;               // a sum of all cities square       (TOBE reworked)

public:
    RouteStatistics();
};
