#include "ConnectionManager.h"

#include <QDebug>

ConnectionManager::ConnectionManager(QObject *parent, bool enableSsl)
    : QObject(parent)
{
    webSocketServer = new QWebSocketServer( "TransportEmpire",
                enableSsl ? QWebSocketServer::SecureMode : QWebSocketServer::NonSecureMode,
                this);

    connect(webSocketServer, &QWebSocketServer::newConnection,
            this, &ConnectionManager::onClientConnected);
    connect(webSocketServer, &QWebSocketServer::closed,
            this, &ConnectionManager::onClose);
}

ConnectionManager::~ConnectionManager() {
    // all unclosed connections
    // are deleted automatically
    // with a server shut down
}

bool ConnectionManager::open(const QHostAddress& address, quint16 port) {
    qDebug() << "ConnectionManager::open(" << port << ")";

    if(webSocketServer->isListening()) {
         qDebug() << "ConnectionManager is already openned.";
        return false;
    }
    return webSocketServer->listen(address, port);
}

void ConnectionManager::close() {
    qDebug() << "ConnectionManager::close()";

    webSocketServer->close();
}

void ConnectionManager::onClientConnected() {
    qDebug() << "ConnectionManager::onClientConnected()";

    QWebSocket *ws = webSocketServer->nextPendingConnection();
    ClientConnection *connection = new ClientConnection(ws, this);
    connect(connection, &ClientConnection::connectionTerminated, this, &ConnectionManager::onClientDisconnected);
    connections << connection;
    emit newConnectionEstablished(connection);
}

void ConnectionManager::onClientDisconnected() {
    qDebug() << "ConnectionManager::onClientDisconnected()";

    ClientConnection *connection = qobject_cast<ClientConnection*>(sender());
    if(!connection) return;
    connections.removeAll(connection);
    connection->deleteLater();
}

void ConnectionManager::onClose() {
    qDebug() << "ConnectionManager::onClose()";

	emit closed();
}
