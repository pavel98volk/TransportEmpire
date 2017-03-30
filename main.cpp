#include <QCoreApplication>

#include "Model/bus.h"
#include "Model/city.h"
#include "Model/path.h"
#include "Model/race.h"
#include "Model/route.h"
#include "Model/bus_type_info.h"
#include "Model/scheduled_race.h"
#include "Model/race_statistics.h"
#include "Model/route_statistics.h"

#include "Server/webserver.h"


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

    WebServer *webServer = new WebServer;	// create web server instace
        QObject::connect(webServer, &WebServer::closed,
                         &a, &QCoreApplication::quit);
        webServer->open(8080);

    int result = a.exec();
    delete webServer;
    return result;
}
