#include "serverclient.hpp"

ServerClient::ServerClient(QWebSocket *soc, ModelBridge *bridge, QObject *parent):
	QObject(parent), modelBridge(bridge), socket(soc)
{
	connect(socket, &QWebSocket::textMessageReceived,
			this,   &ServerClient::onClientTextMessage);
	connect(socket, &QWebSocket::binaryMessageReceived,
			this,   &ServerClient::onClientDataMessage);
	connect(socket, &QWebSocket::disconnected,
			this,   &ServerClient::onClientDisconnected);
}

ServerClient::~ServerClient(){
	if (socket->state() != QAbstractSocket::UnconnectedState)
		socket->abort();
	delete socket;
}

void ServerClient::processJSON(const QJsonDocument &json){
	QJsonObject req = json.object();
	QString request = req["request"].toString();
	QJsonValue data = req["data"];
	processRequest(request, data);
}

void ServerClient::processRequest(const QString &request, const QJsonValue &data){
	if (request == "login") {
		QJsonObject d    = data.toObject();
		QString login    = d["login"].toString();
		QString password = d["password"].toString();
	} else {
		QJsonValue res = modelBridge->processData(request, data);
		if(!res.isNull())
			sendResponse(request, res);
	}
}

void ServerClient::sendResponse(const QString &response, const QJsonValue &data){
	QJsonObject res;
	res["response"] = response;
	res["data"]     = data;

	QJsonDocument json(res);
	QByteArray ba = json.toJson(QJsonDocument::Compact);
	socket->sendTextMessage(ba);
}

void ServerClient::onClientTextMessage(const QString &message){
	QByteArray ba = QByteArray::fromStdString(message.toStdString());
	QJsonDocument json = QJsonDocument::fromJson(ba);
	processJSON(json);
}

void ServerClient::onClientDataMessage(QByteArray message){
	QJsonDocument json = QJsonDocument::fromBinaryData(message);
	processJSON(json);
}

void ServerClient::onClientDisconnected(){
	emit disconnected();
}
