#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include "JsonParsing/route.h"

class WebServer: public QObject{
	Q_OBJECT
public:
	explicit WebServer(QObject *parent = 0);
	~WebServer();

private:	/// <Data/>
	QWebSocketServer *webServer;
	QList <QWebSocket*> webClients;

public:		/// <Controls/>
	void open(quint16 port);
	void close();

private:	/// <Engine/>

private slots:
	void onNewConnection();		// server
	void onErrors();
	void onClose();

	void onClientTextMessage(QString message);
	void onClientDataMessage(QByteArray message);
	void onClientDisconnected();

signals:
	void closed();
};

#endif // WEBSERVER_H
