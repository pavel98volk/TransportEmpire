#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QtWebSockets>

#include "Reply.h"
#include "Request.h"

class ClientConnection: public QObject {
	Q_OBJECT
    Q_DISABLE_COPY(ClientConnection)
public:
    explicit ClientConnection(QWebSocket *_socket, QObject *parent = nullptr);
    ~ClientConnection();

private:		/// <Data/>
    QWebSocket *socket  = nullptr;

private:

signals:
    void requestReceived(const Request&);
    void connectionTerminated();

private slots:
    void onTextMessageReceived(const QString&);
    void onBinaryMessageReceived(const QByteArray&);
};

#endif // SERVERCLIENT_H
