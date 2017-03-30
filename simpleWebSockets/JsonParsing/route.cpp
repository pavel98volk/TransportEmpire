#include "route.h"

void Route::ReadPath(const QJsonArray& jsonArray){
    City temp;
    for(int i = 0; i < jsonArray.size(); ++i){
        temp.Read(jsonArray[i].toObject());
        path.push_back(temp);
    }
}
