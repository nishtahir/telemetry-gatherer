#include <Arduino.h>
#include "ArduinoJson.h"
#include "DHT.h"

#define AUDIO_PIN A0

#define DHTPIN D1
#define DHTTYPE DHT11

JsonObject& prepareTelemetry(JsonBuffer& jsonBuffer);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  dht.begin();
}

void loop() {
  delay(200);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = prepareTelemetry(jsonBuffer);
  json.prettyPrintTo(Serial);
}

JsonObject& prepareTelemetry(JsonBuffer& jsonBuffer) {
  JsonObject& root = jsonBuffer.createObject();
  root["temp"] = dht.readTemperature(/*isFahrenheit=*/true);
  root["hum"] = dht.readHumidity();
  root["sound"] = analogRead(AUDIO_PIN);

  return root;
}
