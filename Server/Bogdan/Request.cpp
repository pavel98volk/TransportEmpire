#include "Request.h"

Request::Request(const QString& _data)
    : textData  { _data },
      binaryData{ QByteArray() },
      isText    { true }
{
}

Request::Request(const QByteArray& _data)
    : binaryData{ _data },
      textData  { QString() },
      isText    { false }
{
}

QJsonDocument Request::getJsonDoc() const {
    // TODO
    return QJsonDocument();
}
