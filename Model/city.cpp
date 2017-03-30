#include "Model/city.h"

City::City()
{
    population = 0;

}

void City::Read(const QJsonObject& json){
        name = json["address"].toString();
        QJsonObject object = json["location"].toObject();
        location.rx() = object["lat"].toDouble();
        location.ry() = object["lng"].toDouble();
 }
