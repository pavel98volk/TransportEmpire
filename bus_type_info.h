#pragma once

#include <QString>

#include <cstdint>

class BusTypeInfo
{
private:
    QString brand;
    QString model;
    uint32_t fuel_consumption;
    uint32_t comfort_level;

public:
    BusTypeInfo();
};
