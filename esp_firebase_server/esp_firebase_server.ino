#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "arduino_secret.h"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String uid;

String databasePath;
String tempPath = "/temperature";
String humPath = "/humidity";
String presPath = "/pressure";
String timePath = "/timestamp";
String parentPath;
FirebaseJson json;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

int timestamp;
float temperature;
float humidity;
float pressure;

unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 180000;

StaticJsonDocument<200> doc;

void initWiFi() {
  WiFi.begin(wifi_ssid, wifi_password);
  // Serial.println();
  // Serial.print("Connecting to WiFi: ");
  // Serial.print(wifi_ssid);
  // Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    // Serial.print('.');
    delay(1000);
  }
  // Serial.println();
  // Serial.println(WiFi.localIP());
  // Serial.println();
}

// Function that gets current epoch time
unsigned long getTime() {
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}

void setup() {
  Serial.begin(115200);

  initWiFi();
  timeClient.begin();

  config.api_key = firebase_api_key;
  auth.user.email = firebase_email;
  auth.user.password = firebase_password;
  config.database_url = firebase_database_url;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.token_status_callback = tokenStatusCallback;
  config.max_token_generation_retry = 5;
  Firebase.begin(&config, &auth);

  while ((auth.token.uid) == "") {
    // Serial.print('.');
    delay(1000);
  }

  uid = auth.token.uid.c_str();
  // Serial.print("User UID: ");
  // Serial.println(uid);

  databasePath = "/UsersData/" + uid + "/readings";
}

void loop() {
  deserializeJson(doc, Serial); // get JSON from Serial - from Atmega

  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    timestamp = getTime();
    parentPath = databasePath + "/" + String(timestamp);

    if (doc["temperature"]) {
      json.set(tempPath.c_str(), String(doc["temperature"]));
      json.set(humPath.c_str(), String(doc["humidity"]));
    } else {
      json.set(tempPath.c_str(), String(24));
      json.set(humPath.c_str(), String(80));
      // json.set(presPath.c_str(), String(70));
    }

    json.set(timePath, String(timestamp));
    Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json);
    // Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
}