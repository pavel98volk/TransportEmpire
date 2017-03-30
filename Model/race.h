#pragma once

#include "Model/route.h"
#include "Model/money.h"
#include "Model/bus_type_info.h"
#include "Model/race_statistics.h"

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

