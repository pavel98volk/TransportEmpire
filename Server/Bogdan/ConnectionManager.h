#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <QObject>
#include <QWebSocket>

#include "ClientConnection.h"

class ConnectionManager: public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(ConnectionManager)
public:
    ConnectionManager(QObject *parent = nullptr, bool enableSsl = false);
    ~ConnectionManager();

private:		/// <Data/>
    QWebSocketServer*           webSocketServer;
    QList<ClientConnection*>    connections;

public:			/// <Controls/>
    bool	open(const QHostAddress& address, quint16 port);
    void	close();

private:

private slots:
    void	onClientConnected();
    void	onClientDisconnected();
    void	onClose();

signals:
    void    newConnectionEstablished(ClientConnection*);
    void	closed();
};

#endif /* WEBSERVER_HPP */
