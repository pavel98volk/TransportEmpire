#pragma once

#include "bus_type_info.h"

#include <QDate>

#include <cstdint>

class BusState;
class Bus
{
private:
    BusTypeInfo* info;
    QDate purchase_date;
    BusState* state;

public:
    Bus();
};

// dynamic properties
class BusState
{
private:
    uint32_t durability;
    QDate last_technical_inspection_date;
    QDate next_technical_inspection_date;
    bool is_avalible;

public:
    BusState();
};
