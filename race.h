#pragma once

#include "route.h"
#include "money.h"
#include "bus_type_info.h"
#include "race_statistics.h"

#include <QTime>

class Race
{
private:
    Route* route;
    QTime duration;
    Amount expenses;
    Amount ticket_price;
    BusTypeInfo* bus_type_info;
    RaceStatistics* statistics;

public:
    Race();
};

