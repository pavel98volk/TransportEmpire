#include <QDebug>
#include <QCoreApplication>

#include "Test/TestSuite.h"

#include "Server/WebServer.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

#ifdef QT_DEBUG
    // Runs all unit tests instantiated as QTestSuite
    QTestSuite::RunAllTests(argc, argv);
#endif

    WebServer server;
    server.setPort(8080);
    server.launch();

    return app.exec();
}
