#include "WebServer.h"

WebServer::WebServer(QObject* parent)
    : QObject(parent),
      mainController   { new MainController(this) },
      connectionManager{ new ConnectionManager(this) }
{
    connect(connectionManager, &ConnectionManager::newConnectionEstablished,
            mainController, &MainController::onConnectionEstablished);
}

void WebServer::setAddress(const QHostAddress& _address) {
    address = _address;
}

void WebServer::setPort(quint16 _port) {
    port = _port;
}

void WebServer::launch() {
    isRunning = connectionManager->open(address, port);
}

void WebServer::stop() {
    connectionManager->close();
    emit stoped();
}

