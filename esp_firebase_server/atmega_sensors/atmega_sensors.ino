#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define pinDHT 3
#define typDHT11 DHT11

DHT dhtSensor(pinDHT, typDHT11);
// SoftwareSerial esp8266(2, 3);

void setup() {
  Serial.begin(115200);
  dhtSensor.begin();
}

void loop() {
  float temperature = dhtSensor.readTemperature();
  float humidity = dhtSensor.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error with reading DHT sensor!");
  } else {
    SendDataToSerial(temperature, humidity);
  }
}

void SendDataToSerial(float temperature, float humidity) {
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  serializeJson(doc, Serial);

  return;
}