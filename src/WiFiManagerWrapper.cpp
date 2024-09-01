#include "WifiManagerWrapper.h"
#include <Arduino.h>

WiFiManagerWrapper::WiFiManagerWrapper() {
    // Serial.begin(115200);
    // delay(1000);
}

void WiFiManagerWrapper::connectToWiFi() {
    Serial.println("Connecting to WiFi...");

    if (!wifiManager.autoConnect("ESP32_AP")) {
        Serial.println("Failed to connect to WiFi and hit timeout");
        delay(3000);
        ESP.restart();
        delay(5000);
    }

    Serial.println("Connected to WiFi");
}