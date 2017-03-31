#include "DAO/dao.h"

bool dao::UploadCity(QSharedPointer<City> city, int& argc, char* argv[])
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

QVector<QSharedPointer<City>> dao::DownloadAllCities(int& argc, char* argv[])
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
    }
}
