#pragma once

#include "database.hxx"
#include "Model/city.h"
#include "Model/route.h"
#include "Model/bus.h"

#include <QVector>
#include <QSharedPointer>

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include "classes.hxx"
#include "classes-odb.hxx"

using namespace std;
using namespace odb::core;

class dao
{
private:
    int argc;
    char** argv;

public:
    dao(int _argc,  char* _argv[])
        : argc{ _argc }, argv{ _argv }
    {
    }

public:
    QVector<QSharedPointer<City>>    DownloadAllCities();
    QVector<QSharedPointer<Route>>   DownloadAllRoutes();
    QVector<QSharedPointer<Bus>>     DownloadAllBuses();

    // return true on success
    bool UploadCity(QSharedPointer<City> city);
    bool UploadRoute(QSharedPointer<Route> route);
    bool UploadBus(QSharedPointer<Bus> bus);

};
