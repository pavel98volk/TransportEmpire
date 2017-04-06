#include "Model/bus_type_info.h"

BusTypeInfo::BusTypeInfo(QString brand_, QString model_, quint32 fuel_, quint32 comfort_)
{
    brand=brand_;
    model=model_;
    fuel_consumption=fuel_;
    comfort_level=comfort_;
}

QString BusTypeInfo::getBrand()
{
    return brand;
}

QString BusTypeInfo::getModel()
{
    return model;
}

quint32 BusTypeInfo::getFuel()
{
    return fuel_consumption;
}

quint32 BusTypeInfo::getComfort()
{
    return comfort_level;
}
