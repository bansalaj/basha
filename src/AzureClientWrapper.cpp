#include "AzureClientWrapper.h"
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <AzureIoTHub.h>
#include <Arduino.h>

// Ensure the correct type for the MQTT protocol
extern "C" IOTHUB_CLIENT_TRANSPORT_PROVIDER MQTT_Protocol;

AzureClientWrapper::AzureClientWrapper(const char* connectionString)
    : connectionString(connectionString) {
    
    iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
    if (iotHubClientHandle == NULL) {
        Serial.println("Failed to create IoT Hub client handle");
        //while (1);
    }
}

void AzureClientWrapper::connectToAzure() {
    if (iotHubClientHandle != NULL) {
        IoTHubClient_LL_DoWork(iotHubClientHandle);
        delay(100);
    }
}

void AzureClientWrapper::sendMessage(const char* message) {
    if (iotHubClientHandle != NULL) {
        IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromString(message);
        if (messageHandle == NULL) {
            Serial.println("Failed to create message handle");
            //while (1);
        }

        if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, NULL, NULL) != IOTHUB_CLIENT_OK) {
            Serial.println("Failed to send message to Azure IoT Hub");
        } else {
            Serial.println("Message sent to Azure IoT Hub");
        }

        IoTHubMessage_Destroy(messageHandle);
    }
}