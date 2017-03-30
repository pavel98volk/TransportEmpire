#pragma once

#include <QPointF>
#include <QString>
#include <QtGlobal>
#include <QJsonValue>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
//#include <iostream>
#include <QDebug>

class City
{
private:
    QString                     name;
    quint32                     population;
    QPointF                     location;
   // double                      lat;
   // double                      lng;
public:
    City();
    void Read(const QJsonObject& json);
    void print(){
        qDebug << location.x() << ' ' << location.y() << ' ' << name << endl;
    }
};
