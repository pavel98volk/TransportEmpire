#pragma once

#include "Model/bus_type_info.h"

#include <QDate>
#include <QtGlobal>
#include <QSharedPointer>

class BusState;
class Bus
{
private:
    QSharedPointer<BusTypeInfo>     info;
    QSharedPointer<BusState>        state;

    QDate                           purchase_date;

public:
    Bus();
};

// dynamic properties
class BusState
{
private:
    quint32                         durability;
    QDate                           last_technical_inspection_date;
    QDate                           next_technical_inspection_date;
    bool                            is_avalible;

public:
    BusState();
};
