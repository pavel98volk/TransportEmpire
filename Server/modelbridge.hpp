#ifndef MODELBRIDGE_HPP
#define MODELBRIDGE_HPP

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class ModelBridge: public QObject{
	Q_OBJECT
public:
	explicit ModelBridge(QObject *parent = 0);

private:		/// <Data/>
	QJsonValue prevData;

public:			/// <Controls/>
	QJsonValue		processData		(const QString &request, const QJsonValue &data);

private:		/// <Engine/>

};

#endif // MODELBRIDGE_HPP
