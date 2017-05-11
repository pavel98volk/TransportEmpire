#include "ClientConnection.h"

ClientConnection::ClientConnection(QWebSocket *_socket, QObject *parent):
    QObject(parent), socket(_socket)
{
    connect(socket, &QWebSocket::binaryMessageReceived, this, &ClientConnection::onBinaryMessageReceived);
    connect(socket, &QWebSocket::textMessageReceived  , this, &ClientConnection::onTextMessageReceived);
    connect(socket, &QWebSocket::disconnected		  , this, &ClientConnection::connectionTerminated);
}

ClientConnection::~ClientConnection() {
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->abort();
    }
    delete socket;
}

void ClientConnection::onTextMessageReceived(const QString& massage) {
    emit requestReceived(Request{massage});
}

void ClientConnection::onBinaryMessageReceived(const QByteArray& massage) {
     emit requestReceived(Request{massage});
}

// ==> All request processing should be inside the Controller
