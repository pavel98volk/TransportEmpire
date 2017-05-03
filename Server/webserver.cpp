#include "webserver.hpp"

WebServer::WebServer(QObject *parent):
	QObject(parent)
{
	webServer = new QWebSocketServer("TransportEmpire",
					QWebSocketServer::NonSecureMode, this);

	connect(webServer, &QWebSocketServer::newConnection,
			this, &WebServer::onClientConnected);
	connect(webServer, &QWebSocketServer::closed,
			this, &WebServer::onClose);
}

WebServer::~WebServer(){
	while(!webClients.isEmpty()){
		ServerClient *client = webClients.takeFirst();
		delete client;
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

void WebServer::onClientConnected(){
	qDebug() << "WebServer::onClientConnected()";
	QWebSocket *ws = webServer->nextPendingConnection();

	ServerClient *client = new ServerClient(ws);
	connect(client, &ServerClient::disconnected, this, &WebServer::onClientDisconnected);
	webClients << client;
}

void WebServer::onClientDisconnected(){
	qDebug() << "WebServer::onClientDisconnected()";
	ServerClient *client = qobject_cast<ServerClient*>(sender());
	if(!client) return;

	webClients.removeAll(client);
	client->deleteLater();
}

void WebServer::onClose(){
	qDebug() << "WebServer::onClose()";
	emit closed();
}
