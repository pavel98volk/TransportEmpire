#pragma once

#include <QtGlobal>

class RouteStatistics
{
private:
    float               quality_factor;       // statistical modeling factor
    quint32             square_coverage;      // a sum of all cities square       (TOBE reworked)
    quint32             population_coverage;  // a sum of all cities population   (TOBE reworked)

public:
    RouteStatistics();
};
