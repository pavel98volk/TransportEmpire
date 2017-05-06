#include "Model/RouteStatistics.h"

RouteStatistics::RouteStatistics(float quality_factor_, quint32 square_coverage_, quint32 population_coverage_)
{
    quality_factor=quality_factor_;
    square_coverage=square_coverage_;
    population_coverage=population_coverage;
}

float RouteStatistics::getQuality()
{
    return quality_factor;
}

quint32 RouteStatistics::getSquareCoverage()
{
    return square_coverage;
}

quint32 RouteStatistics::getPopulationCoverage()
{
    return population_coverage;
}
