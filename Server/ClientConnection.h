#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QtWebSockets>

class ClientConnection: public QObject {
	Q_OBJECT
    Q_DISABLE_COPY(ClientConnection)
public:
    explicit ClientConnection(QWebSocket *_socket, QObject *parent = nullptr);
    ~ClientConnection();

private:		/// <Data/>
    QWebSocket *socket  = nullptr;

public:

signals:
    void textMessageReceived(const QString&);
    void connectionTerminated();
};

#endif // SERVERCLIENT_H
