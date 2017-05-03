#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>
using namespace std;

class ServerClient: public QObject{
	Q_OBJECT
public:
	explicit ServerClient(QWebSocket *soc, QObject *parent = 0);
	~ServerClient();

private:		/// <Data/>
	QWebSocket *socket;

private:		/// <Engine/>
	void	processRequest			(const QString &request,  const QJsonValue &data);
	void	sendResponse			(const QString &response, const QJsonValue &data);

private slots:
	void	onClientTextMessage		(const QString &message);
	void	onClientDataMessage		(QByteArray message);
	void	onClientDisconnected	();

signals:
	void	disconnected			();
};

#endif // SERVERCLIENT_H
