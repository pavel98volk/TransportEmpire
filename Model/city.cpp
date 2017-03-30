#include "Model/city.h"

City::City()
{

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
