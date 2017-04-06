#pragma once

#include "Model/city.h"

#include <QVector>
#include <QSharedPointer>
#include <QDebug>

class Path
{
public:
    QVector<QSharedPointer<City>>       cities;

    qint32                              quality_level;
    double                              milage;

public:
    Path()=default;
    Path(QVector<QSharedPointer<City>> cities_,qint32 quality_level_, double milage_);
    QVector<QSharedPointer<City>> getCities();
    qint32 getQuality();
    double getMilage();
    void ReadPath(const QJsonArray& jsonArray);
    void Debug(){
       for(auto &x: cities) x->Debug();
     }
};

