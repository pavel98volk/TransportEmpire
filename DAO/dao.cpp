#include "DAO/dao.h"

bool dao::UploadCity(QSharedPointer<City> city, int &argc, char* argv[])
{
    try
    {
        auto_ptr<database> db(create_database(argc, argv));

        QSharedPointer<DBCity> dbCity(new DBCity(city->getName(), city->getPopulation(), city->getLocation().x(), city->getLocation().y()));

        transaction t(db->begin());

        db->persist(dbCity);

        t.commit ();

        return true;
    }
    catch (const odb::exception& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

bool dao::UploadBus(QSharedPointer<Bus> bus, int &argc, char* argv[])
{
    try
    {
        auto_ptr<database> db(create_database(argc, argv));

        transaction t(db->begin());

        QSharedPointer<BusState> busState = bus->getState();
        QSharedPointer<BusTypeInfo> busInfo = bus->getInfo();

        QSharedPointer<DBBusState> dbBusState(new DBBusState(busState->getDurability(),busState->getLastInspect(),busState->getNextInspect(),busState->getAvailible()));

        db->persist(dbBusState);

        QSharedPointer<DBBusTypeInfo> dbBusInfo(new DBBusTypeInfo(busInfo->getBrand(),busInfo->getModel(),busInfo->getFuel(),busInfo->getComfort()));

        db->persist(dbBusInfo);

        QSharedPointer<DBBus> dbBus(new DBBus(dbBusInfo,dbBusState,bus->getPurchaseDate()));

        db->persist(dbBus);

        t.commit ();

        return true;
    }
    catch (const odb::exception& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

bool dao::UploadRoute(QSharedPointer<Route> route, int &argc, char* argv[])
{
    try
    {
        auto_ptr<database> db(create_database(argc, argv));

        transaction t(db->begin());

        QSharedPointer<Path> path = route->getPath();
        QSharedPointer<RouteStatistics> statistics = route->getStatistics();
        QVector<QSharedPointer<City>> cities=path->getCities();
        QVector<QSharedPointer<DBCity>> dbCities(cities.size());

        for (int i=0;i<cities.size();i++)
        {
            dbCities[i].reset(new DBCity(cities[i]->getName(), cities[i]->getPopulation(), cities[i]->getLocation().x(), cities[i]->getLocation().y()));
            db->persist(dbCities[i]);
        }

        QSharedPointer<DBPath> dbPath(new DBPath(dbCities,path->getQuality(),path->getMilage()));

        db->persist(dbPath);

        QSharedPointer<DBRouteStatistics> dbRouteStat(new DBRouteStatistics(statistics->getQuality(),statistics->getSquareCoverage(),statistics->getPopulationCoverage()));

        db->persist(dbRouteStat);

        QSharedPointer<DBRoute> dbRoute(new DBRoute(dbPath,dbRouteStat,route->getMilage()));

        db->persist(dbRoute);

        t.commit ();

        return true;
    }
    catch (const odb::exception& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

QVector<QSharedPointer<City>> dao::DownloadAllCities(int &argc, char* argv[])
{
    try
    {
        auto_ptr<database> db(create_database(argc,argv));

        transaction t(db->begin());

        typedef odb::query<DBCity> query;
        typedef odb::result<DBCity> result;

        result r(db->query<DBCity>(query::population>0));

        QVector<QSharedPointer<City>> answer;

        for (result::iterator i(r.begin());i!=r.end();i++)
        {
            QPoint location;
            location.setX(i->getLocationX());
            location.setY(i->getLocationY());
            QSharedPointer<City> current(new City(i->getName(),i->getPopulation(),location));
            answer.push_back(current);
        }

        t.commit();

        return answer;
    }

    catch (const odb::exception& e)
    {
        cerr << e.what() << endl;
        return QVector<QSharedPointer<City>>{};
    }
}

QVector<QSharedPointer<Bus>> dao::DownloadAllBuses(int &argc, char* argv[])
{
    try
    {
        auto_ptr<database> db(create_database(argc,argv));

        transaction t(db->begin());

        typedef odb::query<DBBus> query;
        typedef odb::result<DBBus> result;

        result r(db->query<DBBus>(query::id>=0));

        QVector<QSharedPointer<Bus>> answer;

        for (result::iterator i(r.begin());i!=r.end();i++)
        {
            QSharedPointer<DBBusState> dbBusState = i->getState();
            QSharedPointer<DBBusTypeInfo> dbBusInfo = i->getInfo();

            QSharedPointer<BusState> busState(new BusState(dbBusState->getDurability(),dbBusState->getLast_tech_date(),dbBusState->getNext_tech_date(),dbBusState->getAvailable()));
            QSharedPointer<BusTypeInfo> busInfo(new BusTypeInfo(dbBusInfo->getBrand(),dbBusInfo->getModel(),dbBusInfo->getFuel(),dbBusInfo->getComfort()));

            QSharedPointer<Bus> current(new Bus(busInfo,busState,i->getPurchase_date()));

            answer.push_back(current);
        }

        t.commit();

        return answer;
    }

    catch (const odb::exception& e)
    {
        cerr << e.what() << endl;
        return QVector<QSharedPointer<Bus>>{};
    }
}

QVector<QSharedPointer<Route>> dao::DownloadAllRoutes(int &argc, char* argv[])
{
    try
    {
        auto_ptr<database> db(create_database(argc,argv));

        transaction t(db->begin());

        typedef odb::query<DBRoute> query;
        typedef odb::result<DBRoute> result;

        result r(db->query<DBRoute>(query::id>=0));

        QVector<QSharedPointer<Route>> answer;

        for (result::iterator i(r.begin());i!=r.end();i++)
        {
            QSharedPointer<DBRouteStatistics> dbRouteStatistics = i->getStatistics();
            QSharedPointer<DBPath> dbPath = i->getPath();

            QSharedPointer<RouteStatistics> routeState(new RouteStatistics(dbRouteStatistics->getQualityFactor(),dbRouteStatistics->getSquareCoverage(),dbRouteStatistics->getPopulationCoverage()));
            QVector<QSharedPointer<DBCity>> dbCities = dbPath->getCities();
            QVector<QSharedPointer<City>> cities;
            for (int j=0;j<cities.size();j++)
            {
                cities[j].reset(new City(dbCities[j]->getName(),dbCities[j]->getPopulation(),QPointF(dbCities[j]->getLocationX(),dbCities[j]->getLocationY())));
            }

            QSharedPointer<Path> path(new Path(cities,dbPath->getQuality(),dbPath->getMilage()));

            QSharedPointer<Route> current(new Route(path,routeState,i->getMilage()));

            answer.push_back(current);
        }

        t.commit();

        return answer;
    }

    catch (const odb::exception& e)
    {
        cerr << e.what() << endl;
        return QVector<QSharedPointer<Route>>{};
    }
}

