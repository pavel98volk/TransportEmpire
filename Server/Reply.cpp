#include "Reply.h"

QJsonDocument& Reply::getDataRef() {
    return data;
}

QString Reply::toString() const {
    // TODO
    return QString();
}

QByteArray Reply::toByteArray() const {
    // TODO
    return QByteArray();
}
