#include "dao_test.h"
#include "DAO/dao.h"

#include <QDebug>

// Just an example
void TestDAO::Test1()
{
        QString name = "Pol";
        quint32 population = 12;
        QPoint location;
        location.setX(1);
        location.setY(2);
        QSharedPointer<City> firstCity(new City(name,population,location));

        dao database;

        database.UploadCity(firstCity,argc,argv);

        population=8;
        location.setX(3);
        location.setY(45);
        name="London";
        QSharedPointer<City> secondCity(new City(name,population,location));

        database.UploadCity(secondCity,argc,argv);

        QVector<QSharedPointer<City>> allCities = database.DownloadAllCities(argc,argv);

        QCOMPARE(allCities.size(),2);

        for (int i=0;i<allCities.size();i++)
        {
             if (i==0)
             {
                    QCOMPARE(allCities[i]->getName().toLocal8Bit().constData(),"Pol");
                    QCOMPARE(allCities[i]->getPopulation(),(unsigned int)12);
                    QCOMPARE(allCities[i]->getLocation().x(),1.);
                    QCOMPARE(allCities[i]->getLocation().y(),2.);
             }
             else
             {
                    QCOMPARE(allCities[i]->getName().toLocal8Bit().constData(),"London");
                    QCOMPARE(allCities[i]->getPopulation(),(unsigned int)8);
                    QCOMPARE(allCities[i]->getLocation().x(),3.);
                    QCOMPARE(allCities[i]->getLocation().y(),45.);
             }
         }
}

void TestDAO::Test2()
{
        dao database;

        QSharedPointer<BusState> busState(new BusState((quint32)32,QDate(2016,5,16),QDate(2017,7,12),false));
        QSharedPointer<BusTypeInfo> busInfo(new BusTypeInfo("Mersedes","Benz",15,12));
        QSharedPointer<Bus> myBus(new Bus(busInfo,busState,QDate(2017,4,10)));

        database.UploadBus(myBus,argc,argv);

        QVector<QSharedPointer<Bus>> allBusses = database.DownloadAllBuses(argc,argv);

        QCOMPARE(allBusses.size(),1);
        QCOMPARE(allBusses[0]->getState()->getLastInspect(),QDate(2016,5,16));
        QCOMPARE(allBusses[0]->getState()->getNextInspect(),QDate(2017,7,12));
        QCOMPARE(allBusses[0]->getState()->getAvailible(),false);
        QCOMPARE(allBusses[0]->getInfo()->getBrand().toLocal8Bit().constData(),"Mersedes");
        QCOMPARE(allBusses[0]->getInfo()->getModel().toLocal8Bit().constData(),"Benz");
        QCOMPARE(allBusses[0]->getPurchaseDate(),QDate(2017,4,10));
}

void TestDAO::Test3()
{
        dao database;

        QSharedPointer<RouteStatistics> routeStat(new RouteStatistics(12.0,4,46));
        QVector<QSharedPointer<City>> cities(2);
        cities[0].reset(new City("Berlin",423055,QPoint(2,4)));
        cities[1].reset(new City("Kyiv",23255,QPoint(8,-3)));
        QSharedPointer<Path> path(new Path(cities,46,476.4));
        QSharedPointer<Route> addRoute(new Route(path,routeStat,178.01));
        database.UploadRoute(addRoute,argc,argv);

        QVector<QSharedPointer<Route>> allRoutes = database.DownloadAllRoutes(argc,argv);

        QCOMPARE(allRoutes.size(),1);
        QCOMPARE(allRoutes[0]->getMilage(),178.01);
        QCOMPARE(allRoutes[0]->getPath()->getMilage(),476.4);
}

// DAO test suite instatiation
static TestDAO dao_test_suite_instace;
