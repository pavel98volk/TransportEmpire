#pragma once

#include "Model/city.h"

#include <QVector>
#include <QSharedPointer>

class Path
{
public:
    QVector<QSharedPointer<City>>       cities;

    qint32                              quality_level;
    double                              milage;

public:
    Path();
};

