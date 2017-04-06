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
public:
    QVector<QSharedPointer<City>>    DownloadAllCities(int &argc, char* argv[]);
    QVector<QSharedPointer<Route>>   DownloadAllRoutes(int &argc, char* argv[]);
    QVector<QSharedPointer<Bus>>     DownloadAllBuses(int &argc, char* argv[]);

    // return true on success
    bool UploadCity(QSharedPointer<City> city, int &argc, char* argv[]);
    bool UploadRoute(QSharedPointer<Route> route, int &argc, char* argv[]);
    bool UploadBus(QSharedPointer<Bus> bus, int &argc, char* argv[]);

};
