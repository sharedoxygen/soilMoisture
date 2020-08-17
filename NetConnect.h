#include <SPI.h>
#include <WiFiNINA.h>
#include "ArduinoPrivate.h"

char ssid[] = NET_SSID; 
char pass[] = NET_SSID_PASS; 

#define WiFiConnectDelay 10000

byte mac[6];
int status = WL_IDLE_STATUS;

void displayMacAddress(byte mac[])
{
  for (int i = 5; i >= 0; i--)
  {
    if (mac[i] < 16)
    {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0)
    {
      Serial.print(":");
    }
  }
}

void displayWifiConnectDetails()
{

// print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

// print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC Address: ");
   displayMacAddress(mac);
  Serial.println();

}

extern String wifiConnect()
{

  char macAddress[18];

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(ssid, pass);
    delay(WiFiConnectDelay);
  }
  Serial.println();
  Serial.println("Connected to Network");
  Serial.println();
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  displayWifiConnectDetails();
  Serial.println();

  // Network Router MAC address
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("(BSSID) Router MAC Address: ");
  displayMacAddress(bssid);
  Serial.println();
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("(RSSI) Signal Strength: ");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type: ");
  Serial.println(encryption, HEX);
  Serial.println();

  WiFi.macAddress(mac);
  sprintf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
    
  return macAddress; 
}
