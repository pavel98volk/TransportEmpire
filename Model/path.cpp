#include "Model/path.h"


Path::Path(QVector<QSharedPointer<City> > cities_, qint32 quality_level_, double milage_)
{
    cities=cities_;
    quality_level=quality_level_;
    milage=milage_;
}

QVector<QSharedPointer<City> > Path::getCities()
{
    return cities;
}

qint32 Path::getQuality()
{
    return quality_level;
}

double Path::getMilage()
{
    return milage;
}

void Path::ReadPath(const QJsonArray& jsonArray)
{
    for(int i = 0; i < jsonArray.size(); ++i) {
        cities.push_back(QSharedPointer<City>::create(jsonArray[i].toObject()));
    }
}
