#pragma once

#include "Model/bus.h"
#include "Model/race.h"

#include <QTime>
#include <QSharedPointer>

class ScheduledRace
{
private:
    QSharedPointer<Race>        race;
    QSharedPointer<Bus>         bus;

    QTime                       departure_time;
    QTime                       arrival_time;

public:
    ScheduledRace();
};
