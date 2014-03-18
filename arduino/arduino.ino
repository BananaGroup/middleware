#include <Time.h>

int externalPin = 0;
int corePin = 1;
int extremitiesPin = 2;

void setup() {
  Serial.begin(9600);
}

void loop() {

  float externalTemp = analogRead(externalPin);
  float coreTemp = analogRead(corePin);
  float extremitiesTemp = analogRead(extremitiesPin);

  char externalTempChar[10];
  String externalTempAsString;
  dtostrf(externalTemp,1,2,externalTempChar);
  externalTempAsString = String(externalTempChar);

  char coreTempChar[10];
  String coreTempString;
  dtostrf(externalTemp,1,2,coreTempChar);
  coreTempString = String(coreTempChar);

  char extremitiesTempChar[10];
  String extremitiesTempString;
  dtostrf(extremitiesTemp,1,2,extremitiesTempChar);
  extremitiesTempString = String(extremitiesTempChar);


  String output = "{ \"user_id\": 1, \"readings\": { \"s01\": { \"name\": \"head\", \"value\": 0 } }, \"timetamp\": 1395155056 }";

  String json = "{\"user_id\": 1,";
  json = json + "\"readings\": {";
  // s01
  json = json + "{ \"s01\": ";
  json = json + "\"name\" : \"head\",";
  json = json + "\"value\" :";
  json = json + externalTempAsString;
  json = json + "}";
  //s02
  json = json + "{ \"s02\": ";
  json = json + "\"name\" : \"core\",";
  json = json + "\"value\" :";
  json = json + coreTempString;
  json = json + "}";
  //s03
  json = json + "{ \"s02\": ";
  json = json + "\"name\" : \"extremities\",";
  json = json + "\"value\" :";
  json = json + extremitiesTempString;
  json = json + "}";
  // and timestamps and close json
  json = json + "}, \"timestamp\":";
  json = json + "}";

  Serial.println(json);
  delay(10000);
}

