#include "AzureClientWrapper.h"
#include "config.h"


// Baltimore CyberTrust Root certificate for Azure IoT Hub
const char* azure_root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDdzCCAl+gAwIBAgIEUzDZdzANBgkqhkiG9w0BAQsFADBhMQswCQYDVQQGEwJV\n" \
"UzETMBEGA1UEChMKRFZZIFRydXN0IENvMSAwHgYDVQQDExdEVlkgVHJ1c3QgR29i\n" \
"YWwgQ2VydGlmaWNhdGUwHhcNMTAwMjAxMDAwMDAwWhcNMjUwMjAxMDAwMDAwWjBh\n" \
"MQswCQYDVQQGEwJVUzETMBEGA1UEChMKRFZZIFRydXN0IENvMSAwHgYDVQQDExdE\n" \
"VlkgVHJ1c3QgR29iYWwgQ2VydGlmaWNhdGUwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n" \
"DwAwggEKAoIBAQDw7qMcmDBuF7hELz9Dlq5ZP2vCdwbqSRkLt3UfwvD9FqxltzLo\n" \
"v+1Ta0ydH0+u8NBcH8oMiHz0YOS9x0Fgu9Y5HG4ffMbzS4dce+DFfwaGl95U1wbA\n" \
"OH2zppyg06oP4xZZZlfBMurvlFuKT5l/ZJ49ebzp5XoUJX7+bCNZf47+zjWUXGWu\n" \
"OxbUE9GFrISwDhHhKHcdWDCiA6a/9TrpJhg1hHrwE8g89z5w5yw0IohbWwWtD5pM\n" \
"UpwvOHc7JNZjOEthk81NRO5fAARsBCnR3nbhjtrK3jswDKSgjtnLJ6cmhB37o3G3\n" \
"8+GqZJw8YgvQ1i5RTARfxiCqaTCS70BQtZjHAgMBAAGjgbUwgbIwHQYDVR0OBBYE\n" \
"FGGkyy4RjfZE9cUIuJlFmoGL2WPjMB8GA1UdIwQYMBaAFGGkyy4RjfZE9cUIuJlF\n" \
"moGL2WPjMAwGA1UdEwQFMAMBAf8wHwYDVR0gBBgwFjAIBgZngQwBAgIwDAYKKwYB\n" \
"BAHWeQIFAzAOBgNVHQ8BAf8EBAMCAYYwDQYJKoZIhvcNAQELBQADggEBAAXf8AbI\n" \
"zDE2fxdMV/ORQnV1DoHx5gnxoa9wxdLvsaWyU3MmyIuEhyBX0Ygh0WDYXg8o5CQ9\n" \
"2BGL/HuWslXvwBczXFYj3zDbBS4kp8ClCL3nMHRKpZKeMkjLHrYikZcXfTZCDszH\n" \
"fJVd9kc/BqG0bbhblje3FumVCEHf2VtJt9Cxg2eCyDtdKzoG4R9Lbe4twRCSvE9X\n" \
"uoYIIj8/Xi17mNUt+YTGc+PtN+lElHpysxrDpVjdd9KBfhD6bpVvEyGnbeDBEXtE\n" \
"rWKrL7ZcBbxNGzTJGfLa6kV1xHdT+FJHdzTXn4XZ+ms6cpFw9tYXKuZQLOxWcVAf\n" \
"uFQfCr08k+kmpzE=\n" \
"-----END CERTIFICATE-----\n";

bool connected = false;

// Azure IoT Hub client
az_iot_hub_client iotHubClient;

void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* userContextCallback);

AzureClientWrapper::AzureClientWrapper() {
    IotHub_Init();
    String connString = String("HostName=") + String(IOT_HUB_HOSTNAME) + ";DeviceId=" + String(DEVICE_ID) + ";SharedAccessKey=" + String(SHARED_ACCESS_KEY);

    connectionString = connString.c_str();
}

void AzureClientWrapper::connectToAzure() {

    Serial.println("Connecting to Azure IoT Hub...");
    device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);

    if (device_ll_handle == NULL) {
        Serial.println("Failed to create IoT Hub client handle.");
        return;
    }

    // Set Trusted Certificates
    if (IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_TRUSTED_CERT, azure_root_ca) != IOTHUB_CLIENT_OK) {
        Serial.println("Failed to set trusted certificates.");
        return;
    }

    // Set connection status callback
    if (IoTHubDeviceClient_LL_SetConnectionStatusCallback(device_ll_handle, connectionStatusCallback, NULL) != IOTHUB_CLIENT_OK) {
        Serial.println("Failed to set connection status callback.");
        return;
    }

    Serial.println("Initializing connection to Azure IoT Hub...");

    // Establish connection by calling DoWork until connected
    while (!connected) {
        IoTHubDeviceClient_LL_DoWork(device_ll_handle);
        delay(2000);
    }
}

void AzureClientWrapper::sendMessage(const char* message) {
    IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(message);
    if (message_handle == NULL) {
        Serial.println("Failed to create message handle.");
        return;
    }

    if (IoTHubDeviceClient_LL_SendEventAsync(device_ll_handle, message_handle, NULL, NULL) != IOTHUB_CLIENT_OK) {
        Serial.println("Failed to send message.");
    } else {
        Serial.println("Message sent to Azure IoT Hub.");
    }

    IoTHubMessage_Destroy(message_handle);
}

void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* userContextCallback) {
    if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED) {
        connected = true;
        Serial.println("Successfully connected to Azure IoT Hub.");
    } else {
        connected = false;
        Serial.println("Disconnected from Azure IoT Hub.");
    }
}