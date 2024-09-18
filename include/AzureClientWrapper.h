#ifndef AZURELIENTWRAPPER_H
#define AZURELIENTWRAPPER_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <Esp.h>

class AzureClientWrapper {
public:
    AzureClientWrapper();
    void connectToAzure();
    void sendMessage(const char* message);
private:
    const char* connectionString;
    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;
    //void initClient();
};

#endif