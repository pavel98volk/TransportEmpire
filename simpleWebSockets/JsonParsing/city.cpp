#include "city.h"

void City::Read(const QJsonObject& json){
       name = json["address"].toString();
       QJsonObject object = json["location"].toObject();
       lat = object["lat"].toDouble();
       lng = object["lng"].toDouble();
}

