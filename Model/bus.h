#pragma once

#include "Model/BusTypeInfo.h"

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
    Bus() = default;
    Bus(QSharedPointer<BusTypeInfo> info_, QSharedPointer<BusState> state_, QDate purchase_date_);
    QSharedPointer<BusTypeInfo> getInfo();
    QSharedPointer<BusState> getState();
    QDate getPurchaseDate();
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
    BusState() = default;
    BusState(quint32 durability_, QDate last_technical_inspection_date_, QDate next_technical_inspection_date_,bool is_avalible_);
    quint32 getDurability();
    QDate getLastInspect();
    QDate getNextInspect();
    bool getAvailible();
};
