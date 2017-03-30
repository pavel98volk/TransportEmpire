#include "Model/path.h"

Path::Path()
{

}

void Path::ReadPath(const QJsonArray& jsonArray){
    QSharedPointer<City> temp;
    for(int i = 0; i < jsonArray.size(); ++i){
        temp->Read(jsonArray[i].toObject());
        cities.push_back(temp);
    }
}
