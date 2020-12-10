#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#define Valve2 D1
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "47fdbbbe16...something";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wifi";
char pass[] = "agriproject";
int sensor_pin = A0;

#define DHTPIN 2          // What digital pin we're connected to // D4 for nodemcu

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  pinMode(sensor_pin, INPUT);
  pinMode(Valve2, OUTPUT);
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  int output_value;
  output_value = analogRead(sensor_pin);
  output_value = map(output_value,250,1025,100,0);
  if (output_value <= 40) {
    digitalWrite(Valve2, LOW);
  }
  else if (output_value >= 80) {
    digitalWrite(Valve2, HIGH);
  }
  Blynk.virtualWrite(V4, output_value);
  Serial.print(output_value);
  Serial.print("\n");
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
  delay(2000);
}
