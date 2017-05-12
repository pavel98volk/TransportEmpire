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
    BusTypeInfo() = default;
    BusTypeInfo(QString brand_, QString model_, quint32 fuel_, quint32 comfort_);
    QString getBrand();
    QString getModel();
    quint32 getFuel();
    quint32 getComfort();
};
