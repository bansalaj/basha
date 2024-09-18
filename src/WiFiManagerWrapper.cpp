#include "WifiManagerWrapper.h"
#include <Arduino.h>

// Wi-Fi credentials
const char* WIFI_SSID = "<YOUR_WIFI_SSID>";
const char* WIFI_PASSWORD = "<YOUR_WIFI_PASSWORD>";


WiFiManagerWrapper::WiFiManagerWrapper() {
    // Serial.begin(115200);
    // delay(1000);
}

void WiFiManagerWrapper::connectToWiFi() {
    Serial.println("Connecting to WiFi...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi.");
}