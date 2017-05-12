#ifndef SERVERCLIENT_HPP
#define SERVERCLIENT_HPP

#include <QObject>
#include <QtWebSockets/QWebSocket>

#include <iostream>
using namespace std;

#include "modelbridge.hpp"

class ServerClient: public QObject {
	Q_OBJECT
public:
	explicit ServerClient(QWebSocket *soc, ModelBridge *bridge, QObject *parent = 0);
	~ServerClient();

private:		/// <Data/>
	ModelBridge *modelBridge;
	QWebSocket  *socket;

private:		/// <Engine/>
	void	processJSON				(const QJsonDocument &json);
	void	processRequest			(const QString &request,  const QJsonValue &data);
	void	sendResponse			(const QString &response, const QJsonValue &data = QJsonValue());

private slots:
	void	onClientTextMessage		(const QString &message);
	void	onClientDataMessage		(QByteArray message);
	void	onClientDisconnected	();

signals:
	void	disconnected			();
};

#endif // SERVERCLIENT_HPP
