#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>
using namespace std;

class WebServer: public QObject{
	Q_OBJECT
public:
	explicit WebServer(QObject *parent = 0);
	~WebServer();

private:	/// <Data/>
	QWebSocketServer*		webServer;
	QList <QWebSocket*>		webClients;

public:		/// <Controls/>
	bool	open					(quint16 port);
	void	close					();

private:	/// <Engine/>

private slots:
	void	onNewConnection			();
	void	onClose					();

	void	onClientTextMessage		(const QString &message);
	void	onClientDataMessage		(QByteArray message);
	void	onClientDisconnected	();

signals:
	void	closed();
};

#endif /* WEBSERVER_H */
