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

#include <iostream>

using namespace std;


char prog_name[] = "TransportEmpire.exe";
char modifier[] = "--database";
char db_name[] = "TransportEmpireDB";
char* argv2[3];


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    argv2[0] = new char[strlen(prog_name) + 1];
    argv2[1] = new char[strlen(modifier) + 1];
    argv2[2] = new char[strlen(db_name) + 1];

    strcpy(argv2[0], prog_name);
    strcpy(argv2[1], modifier);
    strcpy(argv2[2], db_name);

    // Runs all unit tests instantiated as QTestSuite
    QTestSuite::RunAllTests(3, argv2);

    QScopedPointer<WebServer> webServer{ new WebServer };
        QObject::connect(webServer.data(), &WebServer::closed,
                         &a, &QCoreApplication::quit);
        webServer->open(8080);

    return a.exec();
}
