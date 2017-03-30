#pragma once

#include <QPoint>
#include <QString>
#include <QtGlobal>

class City
{
private:
    QString                     name;
    quint32                     population;
    QPoint                      location;

public:
    City();
};
