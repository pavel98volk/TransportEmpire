#include <QCoreApplication>

#include "bus.h"
#include "city.h"
#include "path.h"
#include "race.h"
#include "route.h"
#include "bus_type_info.h"
#include "scheduled_race.h"
#include "race_statistics.h"
#include "route_statistics.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Bus bus;
    City city;
    Race race;
    Route route;
    BusTypeInfo bus_type_info;
    ScheduledRace scheduled_race;
    RaceStatistics race_statistics;
    RouteStatistics route_statistics;

    return a.exec();
}
