#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

#include <iostream>
using namespace std;

#include "serverclient.hpp"

class WebServer: public QObject {
	Q_OBJECT
public:
	explicit WebServer(QObject *parent = 0);
	~WebServer();

private:		/// <Data/>
	QWebSocketServer*		webServer;
	QList <ServerClient*>	webClients;

public:			/// <Controls/>
	bool	open					(quint16 port);
	void	close					();

private:		/// <Engine/>

private slots:
	void	onClientConnected		();
	void	onClientDisconnected	();
	void	onClose					();

signals:
	void	closed();
};

#endif /* WEBSERVER_HPP */
