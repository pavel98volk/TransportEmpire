#include "Model/Route.h"

Route::Route(QSharedPointer<Path> path_, QSharedPointer<RouteStatistics> statistics_, double milage_)
{
    path = path_;
    statistics = statistics_;
    milage = milage_;
}

QSharedPointer<Path> Route::getPath()
{
    return path;
}

QSharedPointer<RouteStatistics> Route::getStatistics()
{
    return statistics;
}

double Route::getMilage()
{
    return milage;
}
