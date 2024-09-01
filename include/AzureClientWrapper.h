#ifndef AZURELIENTWRAPPER_H
#define AZURELIENTWRAPPER_H

#include <AzureIoTHub.h>
#include <WiFi.h>

class AzureClientWrapper {
public:
    AzureClientWrapper(const char* connectionString);
    void connectToAzure();
    void sendMessage(const char* message);
private:
    const char* connectionString;
    IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;
    //void initClient();
};

#endif