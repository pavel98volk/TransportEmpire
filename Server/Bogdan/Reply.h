#ifndef REPLY_H
#define REPLY_H

#include <QString>
#include <QJsonDocument>

// must be impelemnted using
// Builder design pattern
class Reply
{
private:
    QJsonDocument data;

public:
    Reply() = default;

public:
    QJsonDocument& getDataRef();

    QString toString() const;
    QByteArray toByteArray() const;

};

#endif // REPLY_H
