#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

// lets define some variable

#define DHPIN 23
#define DHTYPE  DHT11

const int relay = 22;
const int waterLevelSensor = 21;
const int SoilSensor = 19;

int waterLevelData;
int SoilLevelData;

DHT dht(DHPIN,DHTYPE);
BlynkTimer timer;

char auth[] = "Enter Your  Auth Code";
char ssid[] = "WiFi SSID";
char pass[] = "WiFi password";


// tis will send the DHT sensor information

void SendSensorDH()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Blynk.virtualWrite(v5,humidity); 
  Blynk.virtualWrite(v4,temperature);
 //virtual write use to write sensor readigng in blynk
}
// this will send soil and water value we will use analog reads for this value
void SendSensorWaterSoil(){


 waterLevelData = analogRead(waterLevelSensor);
 waterLevel = map(waterLevel, 0,2000,0,25);
 SoilLevelData = analogRead(SoilSensor);
 SoilLevel = map(SoilLevel,0,4000,0,20);

 // send value to blynk

 Blynk.virtualWrite(v7, waterLevel);
 Blynk.virtualWrite(v6,SoilLevel);
}



void setup() {
  // set up serial communication for debugging purpose
  Serial.begin(9600);
  Blynk.begin(auth, ssid,pass);
  dht.begin();
  timer.setInterval(3000L,SendSensorDH);
  timer.setInterval(6000l,SendSensorWaterSoil);

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
