#pragma once

#include"Model/city.h"

#include <QtGlobal>
#include <QSharedPointer>

class Leg
{
private:
    double               distance;
    double               duration;
    qint32               quality_level;

    QSharedPointer<City> start_location;
    QSharedPointer<City> end_location;

public:
    Leg();
};

