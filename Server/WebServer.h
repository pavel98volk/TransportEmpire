#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QScopedPointer>

#include "MainController.h"
#include "ClientConnection.h"
#include "ConnectionManager.h"

class WebServer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(WebServer)
private:
    ConnectionManager*  connectionManager   = nullptr;
    MainController*     mainController      = nullptr;

    QHostAddress        address             = QHostAddress::Any;
    quint16             port                = 0;
    bool                isRunning           = false;

public:
    explicit WebServer(QObject *parent = nullptr);

public:
    void setAddress(const QHostAddress& _address);
    void setPort(quint16 _port);

    void launch();
    void stop();

signals:
    void stoped();

public slots:

};

#endif // WEBSERVER_H
