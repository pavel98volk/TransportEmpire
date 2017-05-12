#include "modelbridge.hpp"

ModelBridge::ModelBridge(QObject *parent):
	QObject(parent)
{}

QJsonValue ModelBridge::processData(const QString &request, const QJsonValue &data){
	if (request == "addRoute") {
		prevData = data;
	} else if (request == "getRoute") {
		return prevData;
	}

	return QJsonValue();
}
