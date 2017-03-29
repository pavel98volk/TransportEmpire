#pragma once

#include "path.h"
#include "route_statistics.h"


class Route
{
private:
    Path path;
    double milage;                  // whole distance wich route takes
    RouteStatistics* statistics;

public:
    Route();
};

