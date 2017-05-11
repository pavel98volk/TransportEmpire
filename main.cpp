#include <QDebug>
#include <QCoreApplication>

#include "Test/TestSuite.h"

#include "Server/webserver.hpp"

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

#ifdef QT_DEBUG
	// Runs all unit tests instantiated as QTestSuite
	QTestSuite::RunAllTests(argc, argv);
#endif

	WebServer server;
	server.open(8080);

	return app.exec();
}
