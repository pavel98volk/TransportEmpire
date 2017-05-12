#include "Model/City.h"

City::City(const QJsonObject& json)
{
    Read(json);
}

City::City(QString name_, quint32 population_, QPointF location_)
{
    name = name_;
    population = population_;
    location = location_;
}

QString City::getName()
{
    return name;
}

quint32 City::getPopulation()
{
    return population;
}

QPointF City::getLocation()
{
    return location;
}

void City::Read(const QJsonObject& json){
        name = json["address"].toString();
        QJsonObject object = json["location"].toObject();
        location.rx() = object["lat"].toDouble();
        location.ry() = object["lng"].toDouble();
 }

