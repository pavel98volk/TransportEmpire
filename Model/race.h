#pragma once

#include "Model/Route.h"
#include "Model/Money.h"
#include "Model/BusTypeInfo.h"
#include "Model/RaceStatistics.h"

#include <QTime>
#include <QSharedPointer>

class Race
{
private:
    QSharedPointer<Route>                   route;
    QSharedPointer<BusTypeInfo>             bus_type_info;
    QSharedPointer<RaceStatistics>          statistics;

    QTime                                   duration;
    Amount                                  expenses;
    Amount                                  ticket_price;

public:
    Race();
};

