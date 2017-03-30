#include <QCoreApplication>
#include "webserver.h"

int main(int argc, char *argv[]){
	QCoreApplication a(argc, argv);

	WebServer *webServer = new WebServer;	// web server
	QObject::connect(webServer, &WebServer::closed,
					 &a, &QCoreApplication::quit);
	webServer->open(1234);

	int ret = a.exec();		// run
	delete webServer;
	return ret;
}
