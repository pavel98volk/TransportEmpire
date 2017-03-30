#pragma once

#include <QString>
#include <QtGlobal>

class BusTypeInfo
{
private:
    QString                     brand;
    QString                     model;
    quint32                     fuel_consumption;
    quint32                     comfort_level;

public:
    BusTypeInfo();
};
