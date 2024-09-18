#ifndef WIFIMANAGERWRAPPER_H
#define WIFIMANAGERWRAPPER_H

#include <WiFi.h>

class WiFiManagerWrapper {
public:
    WiFiManagerWrapper();
    void connectToWiFi();

private:
    WiFiManager wifiManager;
};

#endif