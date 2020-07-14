#include <SPI.h>
#include <Adafruit_SSD1306.h>

#include "NetConnect.h"
#include "APIConnect.h"

// Include Prototypes
void wifiConnect();
void postSensorData(char soilMoistureState[], int soilMoistureValue, int soilMoisturePercent);

//#define NextReading 2700000  // 45 Minutes
//#define NextReading 1800000  // 30 Minute
#define NextReading 60000 // 1 Minutes

// OLED

// Capacivitive Sensor Configuration
const int SensorPin = A0;
const int AirValue = 750;
const int WaterValue = 260;

int intervals = (AirValue - WaterValue) / 3;
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
String soilMoistureState;

// Time

//
// Initial Setup
//
void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  wifiConnect();
}

//
// Infinite Loop
//
void loop()
{
  capactiveSensorDataCollection();
  delay(NextReading);
}
//
// Display Information on LCD
//
void oledDisplay(String status)
{
}

//
// -- Collect Soil Moisture Reading
//
void capactiveSensorDataCollection()
{
  soilMoistureState = "";
  soilMoistureValue = analogRead(SensorPin);
  soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

  if (soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
  {
    soilMoistureState.concat("Wet");
  }
  else if (soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
  {
    soilMoistureState.concat("Moist");
  }
  else if (soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
  {
    soilMoistureState.concat("Dry");
  }
  else
  {
    soilMoistureState.concat("Out-of-Range");
  }

  //oledDisplay (soilMoistureState);
  sendSensorData(soilMoistureState, soilMoistureValue, soilMoisturePercent);

}
