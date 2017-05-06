#pragma once

#include "Model/Path.h"
#include "Model/RouteStatistics.h"

#include <QSharedPointer>

class Route
{
private:
    QSharedPointer<Path>                    path;
    QSharedPointer<RouteStatistics>         statistics;

    double                                  milage;         // whole distance which route takes

public:
    Route() = default;
    Route(QSharedPointer<Path> path_, QSharedPointer<RouteStatistics> statistics_, double milage_);

public:
    QSharedPointer<Path> getPath();
    QSharedPointer<RouteStatistics> getStatistics();
    double getMilage();
};

