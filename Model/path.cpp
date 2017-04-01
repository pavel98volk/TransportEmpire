#include "Model/path.h"

Path::Path()
{

}

void Path::ReadPath(const QJsonArray& jsonArray){
    for(int i = 0; i < jsonArray.size(); ++i){
        cities.push_back(QSharedPointer<City>::create(jsonArray[i].toObject()));
    }
}
