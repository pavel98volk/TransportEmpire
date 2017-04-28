#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class ServerClient: public QObject{
	Q_OBJECT
public:
	explicit ServerClient(QObject *parent = 0);

private:		/// <Data/>

public:			/// <Controls/>

private:		/// <Engine/>

};

#endif // SERVERCLIENT_H
