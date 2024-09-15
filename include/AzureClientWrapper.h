#ifndef AZURELIENTWRAPPER_H
#define AZURELIENTWRAPPER_H

#include <WiFi.h>

class AzureClientWrapper {
public:
    AzureClientWrapper(const char* connectionString);
    void connectToAzure();
    void sendMessage(const char* message);
private:
    const char* connectionString;
    //void initClient();
};

#endif