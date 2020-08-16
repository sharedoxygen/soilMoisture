#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "NetConnect.h"
#include "APIConnect.h"

// Include Prototypes
String wifiConnect();
void postSensorData(char sensorDevice[], char soilMoistureState[], int soilMoistureValue, int soilMoisturePercent);

//#define NextReading 259200000  // 3  Days
//#define NextReading 86400000  // 24 Hours
#define NextReading  7400000    // 2 Hours
 // #define NextReading 60000 // *

// OLED
#define OLED_DISPLAY_DELAY 5000
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Capacivitive Sensor Configuration
#define SENSOR_READ_DELAY 5000
const int SensorPin = A0;
const int AirValue = 725;
const int WaterValue = 360;

int intervals = (AirValue - WaterValue) / 3;
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
String soilMoistureState;

String sensorDevice;
//
// Initial Setup
//
void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
//  while (!Serial)
//   {
//     ; // wait for serial port for USB connect only
//   }
  // OLED
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(OLED_DISPLAY_DELAY); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Connect to WIFI
  sensorDevice = wifiConnect();
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
void oledDisplay(String soilMoistureState, int soilMoisturePercent)
{ 
    display.clearDisplay();


// Soil Moisture Percent   
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Percent ");
    display.println(soilMoisturePercent);
    display.display();
    delay(OLED_DISPLAY_DELAY);
// Soil Moisture Status
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Status ");
    display.println(soilMoistureState);
    display.display();
    delay(OLED_DISPLAY_DELAY);
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
    soilMoistureState.concat("Wet Soil");
  }
  else if (soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
  {
    soilMoistureState.concat("Moist Soil");
  }
  else if (soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
  {
    soilMoistureState.concat("Water Now!");
  }
  else
  {
    soilMoistureState.concat("Out-of-Range");
  }
  delay(SENSOR_READ_DELAY);

// Display on OLED 
  oledDisplay (soilMoistureState, soilMoisturePercent);

// Send to API
  sendSensorData(sensorDevice, soilMoistureState, soilMoistureValue, soilMoisturePercent);
}
