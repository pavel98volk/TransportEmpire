#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "ClientConnection.h"

class MainController : public QObject {
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);

signals:

public slots:
    void onConnectionEstablished(ClientConnection*);
    void onRequestReceived(const QString&);
};

#endif // MAINCONTROLLER_H
