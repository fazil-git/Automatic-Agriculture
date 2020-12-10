#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define Motor D3
#define Valve1 D5
#define TRIGGERPIN D1
#define ECHOPIN    D2
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2379467a61...something";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wifi";
char pass[] = "agriproject";
int sensor_pin = A0;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(sensor_pin, INPUT);
  pinMode(Motor, OUTPUT); // set the digital pin as output.
  pinMode(Valve1, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

}

void loop()
{
  long duration, distance;
  int output_value;
  
  output_value = analogRead(sensor_pin);
  output_value = map(output_value,250,1025,100,0);
  
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  
  if (output_value <= 40) {
    digitalWrite(Valve1, LOW);
  }
  else if (output_value >= 80) {
    digitalWrite(Valve1, HIGH);
  }
  
 /* 
  if (distance <= 2) {
    digitalWrite(Motor, HIGH);
  }
  else if (distance >= 11) {
    digitalWrite(Motor, LOW);
  }
  if (distance <= 12) {
    Blynk.virtualWrite(V0, 255);
}
  else {
    Blynk.virtualWrite(V0, 0);
  }

 if (distance <= 9) {
    Blynk.virtualWrite(V1, 255);
}
  else {
    Blynk.virtualWrite(V1, 0);
  }

   if (distance <= 6) {
    Blynk.virtualWrite(V2, 255);
}
  else {
    Blynk.virtualWrite(V2, 0);
  }

   if (distance <= 4) {
    Blynk.virtualWrite(V3, 255);
}
  else {
    Blynk.virtualWrite(V3, 0);
  }

   if (distance <= 2) {
    Blynk.virtualWrite(V4, 255);
}
  else {
    Blynk.virtualWrite(V4, 0);
  } */

  Blynk.virtualWrite(V4, output_value);
  Serial.print(output_value);
  Serial.print("\n");
  
  Serial.print(distance);
  Serial.println("Cm");
  Blynk.virtualWrite(V5, distance);  //Setup level widget in blynk app
  Blynk.run();

  delay(2000);

}
