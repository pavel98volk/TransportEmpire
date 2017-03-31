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

#include "DAO/dao.h"

#include <iostream>

using namespace std;

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

        QString name = "Pol";
        quint32 population = 12;
        QPoint location;
        location.setX(1);
        location.setY(2);
        QSharedPointer<City> firstCity(new City(name,population,location));

        dao db;

        db.UploadCity(firstCity, argc, argv);

        population=8;
        location.setX(3);
        location.setY(45);
        name="London";
        QSharedPointer<City> secondCity(new City(name,population,location));

        db.UploadCity(secondCity,argc,argv);

        QVector<QSharedPointer<City>> allCities = db.DownloadAllCities(argc,argv);
        for (int i=0;i<allCities.size();i++)
        {
            cout<<allCities[i]->getName().toLocal8Bit().constData()<<' '<<allCities[i]->getPopulation()<<' '<<allCities[i]->getLocation().x()<<' '<<allCities[i]->getLocation().y()<<"\n";
        }

    WebServer *webServer = new WebServer;	// create web server instace
        QObject::connect(webServer, &WebServer::closed,
                         &a, &QCoreApplication::quit);
        webServer->open(8080);



    int result = a.exec();
    delete webServer;
    return result;
}
