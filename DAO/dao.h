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
static QVector<QSharedPointer<City>>    DownloadAllCities(int& argc, char* argv[]);
static QVector<QSharedPointer<Route>>   DownloadAllRoutes();
static QVector<QSharedPointer<Bus>>     DownloadAllBuses();

// return true on success
static bool UploadCity(QSharedPointer<City> city, int& argc, char* argv[]);
static bool UploadRoute(QSharedPointer<Route> route);
static bool UploadBus(QSharedPointer<Bus> bus);

};
