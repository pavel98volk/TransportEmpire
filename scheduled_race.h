#pragma once

#include "bus.h"
#include "race.h"

#include <QTime>

class ScheduledRace
{
private:
    Race* race;
    QTime departure_time;
    QTime arrival_time;
    Bus* bus;

public:
    ScheduledRace();
};
