#ifndef WIFIMANAGERWRAPPER_H
#define WIFIMANAGERWRAPPER_H

#include <WiFiManager.h>

class WiFiManagerWrapper {
public:
    WiFiManagerWrapper();
    void connectToWiFi();

private:
    WiFiManager wifiManager;
};

#endif