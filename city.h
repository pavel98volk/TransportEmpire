#pragma once

#include <cstdint>

#include <QString>
#include <QPoint>

class City
{
private:
    QString name;
    uint32_t population;
    QPoint location;

public:
    City();
};
