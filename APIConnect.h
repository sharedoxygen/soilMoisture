#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiNINA.h>
#include "ArduinoPrivate.h"

#define MESSAGE_SIZE 512
#define SERVICE_URL "/soilmoisturesensor/"

WiFiClient client;


// HTTP Connect
char basicAuthorization[] = API_AUTH;
char server[] = SERVER;
const int port = PORT;

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
        client.println(basicAuthorization);

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

extern void sendSensorData(String sensorDevice, String soilMoistureState, int soilMoistureValue, int soilMoisturePercent)
{

    String sensorData;
    StaticJsonDocument<MESSAGE_SIZE> jsonDocument;    
    
    jsonDocument["sensorDevice"] = sensorDevice;
    jsonDocument["soilState"] = soilMoistureState;
    jsonDocument["sensorValue"] = soilMoistureValue;
    jsonDocument["moisturePercent"] = soilMoisturePercent;

     Serial.println();
     Serial.println("Deserialized JSON Document");
     //serializeJsonPretty(jsonDocument, Serial);

    serializeJsonPretty(jsonDocument, sensorData);
    Serial.println(sensorData);

    postSensorData(sensorData);

}