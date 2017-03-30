#ifndef ROUTE_H
#define ROUTE_H
#include<vector>
#include"city.h"


class Route{
private:
	std::vector<City> path;
public:
	void ReadPath(const QJsonArray& jsonArray);
	void print(){
		for(auto &x: path) x.print();
	}
};

#endif // ROUTE_H
