#ifndef CITY_H
#define CITY_H
#include <QJsonValue>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include <iostream>
using namespace std;

class City
{
private:
	double lat;
	double lng;
	QString name;
public:
	void Read(const QJsonObject& json);
	void print(){
		cout << lat << ' ' << lng << ' ' << name.toStdString() << endl;
	}
};

#endif // CITY_H
