#ifndef CLASSES_HXX
#define CLASSES_HXX

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QDateTime>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QPoint>
#include <QtCore/QtGlobal>
#include <QtCore/QVector>

#include <odb/core.hxx>

#include <odb/qt/lazy-ptr.hxx>

#pragma db object
class DBBusTypeInfo
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long                       id;
	QString                     brand;
	QString                     model;
	quint32                     fuel_consumption;
	quint32                     comfort_level;
	DBBusTypeInfo() {}
public:
	DBBusTypeInfo(const QString& brand_, const QString& model_, quint32 fuel_, quint32 comfort_)
	{
		brand = brand_;
		model = model_;
		fuel_consumption = fuel_;
		comfort_level = comfort_;
	}
	const QString& getBrand() const
	{
		return brand;
	}
	const QString& getModel() const
	{
		return model;
	}
	quint32 getFuel()
	{
		return fuel_consumption;
	}
	quint32 getComfort()
	{
		return comfort_level;
	}
};

#pragma db object
class DBBusState
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long                           id;
	quint32                         durability;
	QDate                           last_technical_inspection_date;
	QDate                           next_technical_inspection_date;
	bool                            is_avalible;
	DBBusState() {};
public:
	DBBusState(quint32 durabitity_, const QDate& last_tech_date, const QDate& next_tech_date, bool is_available_)
	{

		durability = durabitity_;
		last_technical_inspection_date = last_tech_date;
		next_technical_inspection_date = next_tech_date;
		is_avalible = is_available_;
	}
	const QDate& getLast_tech_date() const
	{
		return last_technical_inspection_date;
	}
	const QDate& getNext_tech_date() const
	{
		return next_technical_inspection_date;
	}
	quint32 getDurability()
	{
		return durability;
	}
	bool getAvailable()
	{
		return is_avalible;
	}
};


#pragma db object
class DBBus
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long							  id;
#pragma db not_null
	QSharedPointer<DBBusTypeInfo>     info;
#pragma db not_null
	QSharedPointer<DBBusState>        state;

	QDate                             purchase_date;

	DBBus() {}

public:
	DBBus(QSharedPointer<DBBusTypeInfo> info_, QSharedPointer<DBBusState> state_, const QDate& purchase_date_)
	{

		info = info_;
		state = state_;
		purchase_date = purchase_date_;
	}
	QSharedPointer<DBBusTypeInfo> getInfo() 
	{
		return info;
	}
	QSharedPointer<DBBusState> getState()
	{
		return state;
	}
	const QDate& getPurchase_date() const
	{
		return purchase_date;
	}
};

#pragma db object
class DBCity
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long                       id;
	QString                     name;
	quint32                     population;
    float                     location_x;
    float                     location_y;
	DBCity() {}
public:
    DBCity(const QString& name_, quint32 population_, float location_x_, float location_y_)
	{

		name = name_;
		population = population_;
		location_x = location_x_;
		location_y = location_y_;
	}
	const QString& getName() const
	{
		return name;
	}
	quint32 getPopulation()
	{
		return population;
	}
    const float& getLocationX() const
	{
		return location_x;
    }
    const float& getLocationY() const
	{
		return location_y;
	}
};

#pragma db object
class DBPath
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long                               id;
	QVector<QSharedPointer<DBCity>>     cities;

	qint32                              quality_level;
	double                              milage;
	
	DBPath(){}

public:
	DBPath(QVector<QSharedPointer<DBCity>> cities_, quint32 quality_, double milage_)
	{

		cities = cities_;
		quality_level = quality_;
		milage = milage_;
	}
	QVector<QSharedPointer<DBCity>> getCities()
	{
		return cities;
	}
	quint32 getQuality()
	{
		return quality_level;
	}
	double getMilage()
	{
		return milage;
	}
};

#pragma db object
class DBRaceStatistics
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long						id;
	quint32                     abs_popularity;             // abs_popularity +=
	quint32                     derivative_popularity;      // += derivative_popularity * dt
	float                       trust_factor;               // significance of all other values
															// Statistics has no infulence on any calculation
															// if trust_factor = 0
	DBRaceStatistics() {}

public:
	DBRaceStatistics(quint32 abs_popularity_, quint32 derivate_popularity_, float trust_factor_)
	{

		abs_popularity = abs_popularity_;
		derivative_popularity = derivate_popularity_;
		trust_factor = trust_factor_;
	}
	quint32 getPopularity()
	{
		return abs_popularity;
	}
	quint32 getDerivatePopularity()
	{
		return derivative_popularity;
	}
	float getTrustFactor()
	{
		return trust_factor;
	}
};

#pragma db object
class DBRouteStatistics
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long				id;
	float               quality_factor;       // statistical modeling factor
	quint32             square_coverage;      // a sum of all cities square       (TOBE reworked)
	quint32             population_coverage;  // a sum of all cities population   (TOBE reworked)
	DBRouteStatistics() {}
public:
	DBRouteStatistics(float quality_factor_, quint32 square_coverage_, quint32 population_coverage_) 
	{

		quality_factor = quality_factor_;
		square_coverage = square_coverage_;
		population_coverage = population_coverage_;
	}
	float getQualityFactor()
	{
		return quality_factor;
	}
	quint32 getSquareCoverage()
	{
		return square_coverage;
	}
	quint32 getPopulationCoverage()
	{
		return population_coverage;
	}
};

#pragma db object
class DBRoute
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long									id;
	QSharedPointer<DBPath>                  path;
	QSharedPointer<DBRouteStatistics>       statistics;

	double                                  milage;         // whole distance which route takes
	DBRoute() {}
	
public:
	DBRoute(QSharedPointer<DBPath> path_, QSharedPointer<DBRouteStatistics> statistics_, double milage_) 
	{

		path = path_;
		statistics = statistics_;
		milage = milage_;
	}
	QSharedPointer<DBPath> getPath()
	{
		return path;
	}
	QSharedPointer<DBRouteStatistics> getStatistics()
	{
		return statistics;
	}
	double getMilage()
	{
		return milage;
	}
};

#pragma db object
class DBRace
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long									  id;
	QSharedPointer<DBRoute>                   route;
	QSharedPointer<DBBusTypeInfo>             bus_type_info;
	QSharedPointer<DBRaceStatistics>          statistics;

	QTime                                   duration;
	quint32                                 expenses_grivnas;
	quint32                                 expenses_coins;
	quint32                                 ticket_price_grivnas;
	quint32                                 ticket_price_coins;

	DBRace() {}
public:
	DBRace(QSharedPointer<DBRoute> route_, QSharedPointer<DBBusTypeInfo> bus_, QSharedPointer<DBRaceStatistics> statistics_, const QTime& duration_,
		quint32 exp_grivnas, quint32 exp_coins, quint32 ticket_price_grivnas_, quint32 ticket_price_coins_)
	{

		route = route_;
		bus_type_info = bus_;
		statistics = statistics_;
		duration = duration_;
		expenses_grivnas = exp_grivnas;
		expenses_coins = exp_coins;
		ticket_price_grivnas = ticket_price_grivnas_;
		ticket_price_coins = ticket_price_coins_;
	}

};

#pragma db object
class DBScheduledRace
{
private:
	friend class odb::access;
#pragma db id auto
    unsigned long						  id;
	QSharedPointer<DBRace>        race;
	QSharedPointer<DBBus>         bus;

	QTime                       departure_time;
	QTime                       arrival_time;

	DBScheduledRace(){}
public:
	DBScheduledRace(QSharedPointer<DBRace> race_, QSharedPointer<DBBus> bus_, const QTime& departure_time_, const QTime& arrival_time_)
	{

		race = race_;
		bus = bus_;
		departure_time = departure_time_;
		arrival_time = arrival_time_;
	}
	QSharedPointer<DBRace> getRace() 
	{
		return race;
	}
	QSharedPointer<DBBus> getBus()
	{
		return bus;
	}
	const QTime& getDepartureTime() const
	{
		return departure_time;
	}
	const QTime& getArrivalTime() const
	{
		return arrival_time;
	}
};

#endif // CLASSES_HXX
