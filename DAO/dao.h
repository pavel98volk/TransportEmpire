#pragma once

#include "Model/city.h"
#include "Model/route.h"
#include "Model/bus.h"

#include <QVector>
#include <QSharedPointer>

class dao
{
public:
static QVector<QSharedPointer<City>>    DownloadAllCities();
static QVector<QSharedPointer<Route>>   DownloadAllRoutes();
static QVector<QSharedPointer<Bus>>     DownloadAllBuses();

// return true on success
static bool UploadCity(QSharedPointer<City> city);
static bool UploadRoute(QSharedPointer<Route> route);
static bool UploadBus(QSharedPointer<Bus> bus);
};
