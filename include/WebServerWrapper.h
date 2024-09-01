#ifndef WEBSERVERWRAPPER_H
#define WEBSERVERWRAPPER_H

#include <WebServer.h>

class WebServerWrapper {
public:
    WebServerWrapper();
    void startServer();
    void handleClient();
private:
    WebServer server;
    void handleRoot();
};

#endif