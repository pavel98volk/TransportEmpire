#include "MainController.h"

MainController::MainController(QObject *parent)
    : QObject(parent)
{
}

void MainController::onConnectionEstablished(ClientConnection* connection) {
    connect(connection, &ClientConnection::textMessageReceived,
            this, &MainController::onRequestReceived);
}

void MainController::onRequestReceived(const QString& request) {
    // ==> The request processing and dispatching
    // should be here
}
