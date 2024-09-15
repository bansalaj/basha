#include "AzureClientWrapper.h"
#include <az_core.h>
#include <az_iot_hub_client.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>  // For MQTT


// Define your WiFiClientSecure
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

// Azure IoT Hub client
az_iot_hub_client iotHubClient;
// Ensure the correct type for the MQTT protocol

// Initialize the AzureClientWrapper with connectionString
AzureClientWrapper::AzureClientWrapper(const char* connectionString) {
    this->connectionString = connectionString;
    az_iot_hub_client_init(&iotHubClient, az_span_create_from_str("IOT_HUB_HOSTNAME"), az_span_create_from_str("DEVICE_ID"), NULL);
}

void AzureClientWrapper::connectToAzure() {
    Serial.println("Connecting to Azure IoT Hub...");

    mqttClient.setServer("IOT_HUB_HOSTNAME", 8883);

    if (mqttClient.connect("DEVICE_ID", "SAS_TOKEN", "")) {
        Serial.println("Connected to Azure IoT Hub!");
    } else {
        Serial.println("Connection to Azure IoT Hub failed!");
    }
}

void AzureClientWrapper::sendMessage(const char* message) {
    // Topic for sending telemetry to IoT Hub
    const char* telemetry_topic = "devices/your-device-id/messages/events/";

    if (mqttClient.publish(telemetry_topic, message)) {
        Serial.println("Message sent successfully");
    } else {
        Serial.println("Failed to send message");
    }
}