#include <ArduinoJson.h>
#include <WiFiNINA.h>

#define MESSAGE_SIZE 200
#define SERVICE_URL "/soilmoisturesensor/"

WiFiClient client;
DynamicJsonDocument dynamicJsonDocument(MESSAGE_SIZE);

// HTTP Connect
char server[] = "10.0.0.3";
const int port = 8000;

String sensorData;
String HTTP;

//char postMessage[100];
//sprintf(postMessage," POST %s HTTP/1.1", webpage);

void postSensorData()
{

    HTTP.concat(" POST ");
    HTTP.concat(SERVICE_URL);
    HTTP.concat(" HTTP/1.1 ");
    if (client.connect(server, port))
    {
        Serial.println("Connected to Server");
        Serial.println(HTTP);
        Serial.println();

        client.stop();
        HTTP="";
    }
    else
    {
        Serial.println("Connection Failed");
    }
}

extern void sendSensorData(String soilMoistureState, int soilMoistureValue, int soilMoisturePercent)
{

    dynamicJsonDocument["soilState"] = soilMoistureState;
    dynamicJsonDocument["sensorValue"] = soilMoistureValue;
    dynamicJsonDocument["moisturePercent"] = soilMoisturePercent;

    // Serial.println();
    // Serial.println("Dynamic JSON Document");
    // serializeJsonPretty(dynamicJsonDocument, Serial);
    Serial.println();
    Serial.println("JSON Message for POST");
    serializeJsonPretty(dynamicJsonDocument, sensorData);
    Serial.println(sensorData);
    sensorData = "";

    postSensorData();
}