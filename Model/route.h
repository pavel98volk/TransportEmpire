#pragma once

#include "Model/path.h"
#include "Model/route_statistics.h"

#include <QSharedPointer>

class Route
{
private:
    QSharedPointer<Path>                    path;
    QSharedPointer<RouteStatistics>         statistics;

    double                                  milage;         // whole distance which route takes

public:
    Route();
};

