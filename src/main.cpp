#include <Arduino.h>
#include "WifiManagerWrapper.h"
#include "WebServerWrapper.h"
#include "AzureClientWrapper.h"



WiFiManagerWrapper wifiManagerWrapper;
WebServerWrapper webServerWrapper;
AzureClientWrapper azureClientWrapper;  // No need to pass the connection string

void initializeTime();

void setup() {
    Serial.begin(115200);
    delay(1000);

    wifiManagerWrapper.connectToWiFi();

    // // Start the web server (if needed)
    // webServerWrapper.startServer();

    initializeTime();

    // Connect to Azure IoT Hub
    azureClientWrapper.connectToAzure();
}

void loop() {
    webServerWrapper.handleClient();

    // Send a telemetry message to Azure IoT Hub periodically
    azureClientWrapper.sendMessage("{\"temperature\": 24.5}");
}

void initalizeTime() {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    Serial.println("Waiting for NTP time sync...");
    time_t now = time(nullptr);

    while (now < 8 * 3600 * 2) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }

    Serial.println("");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
}