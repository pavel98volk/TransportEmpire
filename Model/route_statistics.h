#pragma once

#include <QtGlobal>

class RouteStatistics
{
private:
    float               quality_factor;       // statistical modeling factor
    quint32             square_coverage;      // a sum of all cities square       (TOBE reworked)
    quint32             population_coverage;  // a sum of all cities population   (TOBE reworked)

public:
    RouteStatistics()=default;
    RouteStatistics(float quality_factor_, quint32 square_coverage_, quint32 population_coverage_);
    float getQuality();
    quint32 getSquareCoverage();
    quint32 getPopulationCoverage();
};
