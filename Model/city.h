#pragma once

#include <QPoint>
#include <QString>
#include <QtGlobal>

class City
{
private:
    QString                     name;
    quint32                     population;
    QPointF                      location;

public:
    City();
    City(QString name_, quint32 population_, QPointF location_);
    QString getName();
    quint32 getPopulation();
    QPointF getLocation();
};
