char ssid[] = "SKYNET";
char wifiPassword[] = "123456787";

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "DHT.h"

#define DHTPIN 12     
#define DHTTYPE DHT11   // DHT 11

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "00e00860-abc5-11e9-be3b-372b0d2759ae";
char password[] = "9e1447069cdf461138dfcc8a068635aa44eb4095";
char clientID[] = "c1d64b30-c482-11e9-9f0a-fd8975d06205";

float RawValue= 0;
float Voltage = 0;
float tempC = 0;
float tempF = 0;
float tempK = 0;
const int analogIn = A0;
DHT dht(DHTPIN, DHTTYPE);
 float h = dht.readHumidity();
void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  Serial.println(F("DHTxx test!"));
}

void loop() {
  Cayenne.loop();
 RawValue = analogRead(analogIn);
Voltage = (RawValue / 10.0); // 5000 to get millivots.
tempC = Voltage;
tempF = (tempC * 1.8) + 32; // conver to F
tempK = (tempC + 273); // conver to F
Serial.print("Raw Value = " ); // shows pre-scaled value
Serial.print(RawValue);
Serial.print("\t milli volts = "); // shows the voltage measured
Serial.print(Voltage,0); //
Serial.print("\t Temperature in C = ");
Serial.print(tempC,1);
Serial.print("\t Temperature in F = ");
Serial.print(tempF,1);
Serial.print("\t Temperature in K = ");
Serial.println(tempK,1);
delay(10);
// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
   if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  //Cayenne.virtualWrite(V1, (float)RawValue);
  //Cayenne.virtualWrite(V2, (float)Voltage);
  Cayenne.virtualWrite(V3, (float)tempC);
  Cayenne.virtualWrite(V4, (float)tempF);
  Cayenne.virtualWrite(V5, (float)tempK);
  Cayenne.virtualWrite(V6, dht.readHumidity());
  
  delay(200);
}
