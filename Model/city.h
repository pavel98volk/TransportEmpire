#pragma once

#include <QPointF>
#include <QString>
#include <QtGlobal>
#include <QJsonValue>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>

#include <QDebug>

class City
{
private:
    QString                     name;
    quint32                     population;
    QPointF                     location;

public:
    City();
    
public:
    void Read(const QJsonObject& json);
    void Debug() {
        qDebug() << location.x() << location.y() << name << endl;
    }
};
