#ifndef REQUEST_H
#define REQUEST_H

#include <QString>
#include <QJsonDocument>

class Request
{
private:
    const QString& textData;
    const QByteArray& binaryData;

    bool isText;

public:
    Request(const QString& _data);
    Request(const QByteArray& _data);

public:
    QJsonDocument getJsonDoc()  const;

// TODO:
//    QString getRequestType()  const;
//    QString getUrl()          const;
//    QString getData()         const;
};

#endif // REQUEST_H
