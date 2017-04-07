#include "dao_test.h"
#include "DAO/dao.h"

#include <QDebug>

// Just an example
void TestDAO::CitiesTableTest()
{
        dao database{ argc, argv };

        QString name;
        quint32 population;
        QPoint location;

        name = "Kiev";
        population = 2804000;
        location.setX(30);
        location.setY(50);

        QSharedPointer<City> kievCity(new City(name, population, location));

        database.UploadCity(kievCity);

        name = "London";
        population = 8674000;
        location.setX(3);
        location.setY(45);

        QSharedPointer<City> londonCity(new City(name, population, location));

        database.UploadCity(londonCity);

        QVector<QSharedPointer<City>> allCities = database.DownloadAllCities();

        QCOMPARE(allCities.size(), 2);

        for (int i = 0; i < allCities.size(); i++)
        {
             if (i == 0)
             {
                    QCOMPARE(allCities[i]->getName().toLocal8Bit().constData(), "Kiev");
                    QCOMPARE(allCities[i]->getPopulation(), (unsigned int) 2804000);
                    QCOMPARE(allCities[i]->getLocation().x(), 30.0);
                    QCOMPARE(allCities[i]->getLocation().y(), 50.0);
             }
             else
             {
                    QCOMPARE(allCities[i]->getName().toLocal8Bit().constData(), "London");
                    QCOMPARE(allCities[i]->getPopulation(), (unsigned int) 8674000);
                    QCOMPARE(allCities[i]->getLocation().x(), 3.0);
                    QCOMPARE(allCities[i]->getLocation().y(), 45.0);
             }
         }
}

void TestDAO::BusesTableTest()
{
        dao database{ argc, argv };

        QSharedPointer<BusState> busState(new BusState((quint32) 32, QDate(2016,5,16), QDate(2017,7,12), false));
        QSharedPointer<BusTypeInfo> busInfo(new BusTypeInfo("Mersedes", "Benz", 15, 12));
        QSharedPointer<Bus> myBus(new Bus(busInfo, busState, QDate(2017, 4, 10)));

        database.UploadBus(myBus);

        QVector<QSharedPointer<Bus>> allBusses = database.DownloadAllBuses();

        QCOMPARE(allBusses.size(),1);
        QCOMPARE(allBusses[0]->getState()->getLastInspect(), QDate(2016, 5, 16));
        QCOMPARE(allBusses[0]->getState()->getNextInspect(), QDate(2017, 7, 12));
        QCOMPARE(allBusses[0]->getState()->getAvailible(), false);
        QCOMPARE(allBusses[0]->getInfo()->getBrand().toLocal8Bit().constData(), "Mersedes");
        QCOMPARE(allBusses[0]->getInfo()->getModel().toLocal8Bit().constData(), "Benz");
        QCOMPARE(allBusses[0]->getPurchaseDate(), QDate(2017, 4, 10));
}

void TestDAO::RoutesTableTest()
{
        dao database{ argc, argv };

        QSharedPointer<RouteStatistics> routeStat(new RouteStatistics(12.0, 4, 46));
        QVector<QSharedPointer<City>> cities
        {
           QSharedPointer<City>::create("Berlin", 3502000, QPoint(2, 4)),
           QSharedPointer<City>::create("Tokyo", 13620000, QPoint(8, -3))
        };
        QSharedPointer<Path> path(new Path(cities, 46, 476.4));
        QSharedPointer<Route> addRoute(new Route(path, routeStat, 178.01));

        database.UploadRoute(addRoute);

        QVector<QSharedPointer<Route>> allRoutes = database.DownloadAllRoutes();

        QCOMPARE(allRoutes.size(), 1);
        QCOMPARE(allRoutes[0]->getMilage(), 178.01);
        QCOMPARE(allRoutes[0]->getPath()->getMilage(), 476.4);
}

// DAO test suite instatiation
static TestDAO dao_test_suite_instace;
