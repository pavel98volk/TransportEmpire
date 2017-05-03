#include "serverclient.hpp"

ServerClient::ServerClient(QWebSocket *soc, QObject *parent):
	QObject(parent), socket(soc)
{
	connect(socket, &QWebSocket::textMessageReceived  , this, &ServerClient::onClientTextMessage);
	connect(socket, &QWebSocket::binaryMessageReceived, this, &ServerClient::onClientDataMessage);
	connect(socket, &QWebSocket::disconnected		  , this, &ServerClient::onClientDisconnected);
}

ServerClient::~ServerClient(){
	if (socket->state() != QAbstractSocket::UnconnectedState)
		socket->abort();
	delete socket;
}

void ServerClient::processRequest(const QString &request, const QJsonValue &data){
	if (request == ""){
		sendResponse(request, data);
	} else if (request == "") {
		//
	} else {
		qDebug() << "ServerClient::processRequest(): unknown request";
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

	QJsonObject req = json.object();
	QString request = req["request"].toString();
	QJsonValue data = req["data"];
	processRequest(request, data);
}

void ServerClient::onClientDataMessage(QByteArray message){
	Q_UNUSED(message)
}

void ServerClient::onClientDisconnected(){
	emit disconnected();
}
