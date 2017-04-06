#include "Model/bus.h"

Bus::Bus(QSharedPointer<BusTypeInfo> info_, QSharedPointer<BusState> state_, QDate purchase_date_)
{
    info=info_;
    state=state_;
    purchase_date=purchase_date_;
}

QSharedPointer<BusTypeInfo> Bus::getInfo()
{
    return info;
}

QSharedPointer<BusState> Bus::getState()
{
    return state;
}

QDate Bus::getPurchaseDate()
{
    return purchase_date;
}

BusState::BusState(quint32 durability_, QDate last_technical_inspection_date_, QDate next_technical_inspection_date_, bool is_avalible_)
{
    durability=durability_;
    last_technical_inspection_date=last_technical_inspection_date_;
    next_technical_inspection_date=next_technical_inspection_date_;
    is_avalible=is_avalible_;
}

quint32 BusState::getDurability()
{
    return durability;
}

QDate BusState::getLastInspect()
{
    return last_technical_inspection_date;
}

QDate BusState::getNextInspect()
{
    return next_technical_inspection_date;
}

bool BusState::getAvailible()
{
    return is_avalible;
}
