#include "webserver.hpp"

WebServer::WebServer(QObject *parent):
	QObject(parent)
{
	webServer = new QWebSocketServer("Transport Database",
									 QWebSocketServer::NonSecureMode,
									 this);

	connect(webServer, &QWebSocketServer::newConnection,
			this, &WebServer::onNewConnection);
	connect(webServer, &QWebSocketServer::closed,
			this, &WebServer::onClose);
}

WebServer::~WebServer(){
	while(!webClients.isEmpty()){
		QWebSocket *ws = webClients.takeFirst();
		ws->abort();
		delete ws;
	}
}

bool WebServer::open(quint16 port){
	qDebug() << "WebServer::open(" << port << ")";
	return webServer->listen(QHostAddress::Any, port);
}

void WebServer::close(){
	qDebug() << "WebServer::close()";
	webServer->close();
}

void WebServer::onNewConnection(){
	qDebug() << "WebServer::onNewConnection()";
	QWebSocket *ws = webServer->nextPendingConnection();

	connect(ws, &QWebSocket::textMessageReceived  , this, &WebServer::onClientTextMessage);
	connect(ws, &QWebSocket::binaryMessageReceived, this, &WebServer::onClientDataMessage);
	connect(ws, &QWebSocket::disconnected		  , this, &WebServer::onClientDisconnected);

	webClients << ws;
}

void WebServer::onClose(){
	emit closed();
}

void WebServer::onClientTextMessage(const QString &message){
	QWebSocket *ws = qobject_cast<QWebSocket*>(sender());
	if(!ws) return;

	QByteArray ba = QByteArray::fromStdString(message.toStdString());
	QJsonDocument json(QJsonDocument::fromJson(ba));

	QJsonObject req = json.object();
	QString request = req["request"].toString();
	QJsonValue data = req["data"];
}

void WebServer::onClientDataMessage(QByteArray message){
	QWebSocket *ws = qobject_cast<QWebSocket*>(sender());
	if(!ws) return;
	Q_UNUSED(message)
}

void WebServer::onClientDisconnected(){
	qDebug() << "WebServer::onClientDisconnected()";
	QWebSocket *ws = qobject_cast<QWebSocket*>(sender());
	if(!ws) return;

	webClients.removeAll(ws);
	ws->deleteLater();
}
