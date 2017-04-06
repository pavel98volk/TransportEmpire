#include <QCoreApplication>
#include <QScopedPointer>
#include <QDebug>

#include "Test/test_suite.h"

#include "Model/bus.h"
#include "Model/city.h"
#include "Model/path.h"
#include "Model/race.h"
#include "Model/route.h"
#include "Model/bus_type_info.h"
#include "Model/scheduled_race.h"
#include "Model/race_statistics.h"
#include "Model/route_statistics.h"

#include "Server/webserver.h"

#include "DAO/dao.h"


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Runs all unit tests instantiated as QTestSuite
    QTestSuite::RunAllTests(argc, argv);

    QScopedPointer<WebServer> webServer{ new WebServer };
        QObject::connect(webServer.data(), &WebServer::closed,
                         &a, &QCoreApplication::quit);
        webServer->open(8080);

    return a.exec();
}
