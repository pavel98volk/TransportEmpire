
#include "Server/webserver.h"
#include "Model/route.h"

WebServer::WebServer(QObject *parent):
	QObject(parent)
{
	webServer = new QWebSocketServer("Hello world",
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

void WebServer::open(quint16 port){
	qDebug() << "open(" << port << ")";
	webServer->listen(QHostAddress::Any, port);
}

void WebServer::close(){
	qDebug() << "close()";
	webServer->close();
}

void WebServer::onNewConnection(){
	qDebug() << "client new connection";
	QWebSocket *ws = webServer->nextPendingConnection();

	connect(ws, &QWebSocket::textMessageReceived  , this, &WebServer::onClientTextMessage);
	connect(ws, &QWebSocket::binaryMessageReceived, this, &WebServer::onClientDataMessage);
	connect(ws, &QWebSocket::disconnected		  , this, &WebServer::onClientDisconnected);

	webClients << ws;
}

void WebServer::onErrors(){

}

void WebServer::onClose(){
	emit closed();
}

void WebServer::onClientTextMessage(QString message){
    QWebSocket *ws = qobject_cast<QWebSocket*>(sender());
    if(!ws) return;

    if(message == "close()") close();

    // qDebug() << message;
    // Route r;
    // QByteArray arr = QByteArray::fromStdString(message.toStdString());
    // QJsonDocument doc(QJsonDocument::fromJson(arr));
    // r.ReadPath(doc.array());
    // r.print();
    // for(QWebSocket *wsc: webClients)
    //      wsc->sendTextMessage(message);
}

void WebServer::onClientDataMessage(QByteArray message){
	QWebSocket *ws = qobject_cast<QWebSocket*>(sender());
	if(!ws) return;

	ws->sendBinaryMessage(message);
}

void WebServer::onClientDisconnected(){
	qDebug() << "client disconnected";
	QWebSocket *ws = qobject_cast<QWebSocket*>(sender());
	if(!ws) return;

	webClients.removeAll(ws);
	ws->deleteLater();
}
