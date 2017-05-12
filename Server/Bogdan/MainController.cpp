#include "MainController.h"

MainController::MainController(QObject *parent)
    : QObject(parent)
{
}

void MainController::onConnectionEstablished(ClientConnection* connection) {
    connect(connection, &ClientConnection::requestReceived,
            this, &MainController::onRequestReceived);
    // TODO: also reply must be handled and sent back in some way
}

void MainController::onRequestReceived(const Request& request) {
    Q_UNUSED(request)
    // TODO
    // ==> The request processing and dispatching
    // should be here
}
