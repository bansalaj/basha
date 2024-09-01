#include <Arduino.h>
#include "WifiManagerWrapper.h"
#include "WebServerWrapper.h"
#include "AzureClientWrapper.h"

// replace with actual connection string
const char* connectionString = "HostName=iot-hub-esp32.azure-devices.net;DeviceId=esp32-device;SharedAccessKey=your-shared";


WiFiManagerWrapper wifiManagerWrapper;
WebServerWrapper webServerWrapper;

void setup() {
    Serial.begin(115200);
    delay(1000);

    wifiManagerWrapper.connectToWiFi();
    webServerWrapper.startServer();
}

void loop() {
    webServerWrapper.handleClient();
}