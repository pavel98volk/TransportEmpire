#pragma once

#include <QPointF>
#include <QString>
#include <QtGlobal>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

class City
{
private:
    QString                     name;
    quint32                     population = 0;
    QPointF                     location;

public:
    City() = default;
    City(const QJsonObject &json);
    City(QString name_, quint32 population_, QPointF location_);

public:
    QString getName();
    quint32 getPopulation();
    QPointF getLocation();

public:
    void Read(const QJsonObject& json);
    void Debug() {
        qDebug() << location.x() << location.y() << name << endl;
    }


};
