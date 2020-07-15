#include <ArduinoJson.h>
#include <WiFiNINA.h>

#define MESSAGE_SIZE 200
#define SERVICE_URL "/soilmoisturesensor/"

WiFiClient client;
DynamicJsonDocument dynamicJsonDocument(MESSAGE_SIZE);

// HTTP Connect
char server[] = "10.0.0.3";
const int port = 8000;

//char postMessage[100];
//sprintf(postMessage," POST %s httpPost/1.1", webpage);

void postSensorData(String sensorData)
{
    String httpPost;

    httpPost.concat(" POST ");
    httpPost.concat(SERVICE_URL);
    httpPost.concat(" HTTP/1.1 ");

    if (client.connect(server, port))
    {
        
        client.println(httpPost);
        client.print("Content-Type: ");
        client.println("application/json");

        client.print("Content-Length: ");
        client.println(sensorData.length());

        client.print("Authorization: ");
        client.println("Basic ZGV2ZWxvcGVyOnNlY3VyZQ==");

        client.print("Host: ");
        client.println(server);

        client.println("Connection: close");

        client.println();
        client.println(sensorData);

        client.stop();
        httpPost = "";
    }
    else
    {
        Serial.println("Connection Failed");
    }
}

extern void sendSensorData(String sensorLocation, String soilMoistureState, int soilMoistureValue, int soilMoisturePercent)
{
    String sensorData;

    dynamicJsonDocument["sensorLocation"] = sensorLocation;
    dynamicJsonDocument["soilState"] = soilMoistureState;
    dynamicJsonDocument["sensorValue"] = soilMoistureValue;
    dynamicJsonDocument["moisturePercent"] = soilMoisturePercent;

    // Serial.println();
    // Serial.println("Dynamic JSON Document");
    // serializeJsonPretty(dynamicJsonDocument, Serial);
    Serial.println();
    Serial.println("Post Message ");
    serializeJsonPretty(dynamicJsonDocument, sensorData);
    Serial.println(sensorData);

    postSensorData(sensorData);
    sensorData = "";
}