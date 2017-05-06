#include "ClientConnection.h"

ClientConnection::ClientConnection(QWebSocket *_socket, QObject *parent):
    QObject(parent), socket(_socket)
{
    connect(socket, &QWebSocket::textMessageReceived, this, &ClientConnection::textMessageReceived);
    connect(socket, &QWebSocket::disconnected		, this, &ClientConnection::connectionTerminated);
}

ClientConnection::~ClientConnection() {
    if (socket->state() != QAbstractSocket::UnconnectedState) {
		socket->abort();
    }
    delete socket;
}

// ==> All request processing should be inside the Controller
