#include "WebServerWrapper.h"
#include <Arduino.h>

WebServerWrapper::WebServerWrapper() : server(80) {
    // Serial.begin(115200);
    // delay(1000);
}

void WebServerWrapper::startServer() {
    server.on("/", std::bind(&WebServerWrapper::handleRoot, this));
    server.begin();
}

void WebServerWrapper::handleClient() {
    server.handleClient();
}

void WebServerWrapper::handleRoot() {
    String html = "<!DOCTYPE html><html><head><title>ESP32 Web Server</title></head><body>";
    html += "<h1>Hello from ESP32!</h1>";
    html += "<p>This is a sample web page served by the ESP32 web server.</p>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}