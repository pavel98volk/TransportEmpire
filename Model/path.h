#pragma once

#include "Model/city.h"
#include "Model/leg.h"

#include <QVector>
#include <QSharedPointer>
#include <QDebug>

class Path
{
public:
    QString                             id;

    QVector<QSharedPointer<City>>       cities;
    QVector<quint32>                    cities_indices;
    QVector<QSharedPointer<Leg>>        legs;


    qint32                              quality_level;
    double                              milage;
    double                              duration;

public:
    Path()=default;
    Path(QVector<QSharedPointer<City>> cities_,qint32 quality_level_, double milage_, QVector<quint32> indices, QVector<QSharedPointer<Leg>> legs_, double duration_);
    QVector<QSharedPointer<City>> getCities();
    qint32 getQuality();
    double getMilage();
    void ReadPath(const QJsonArray& jsonArray);
    void Debug(){
       for(auto &x: cities) x->Debug();
     }
};

