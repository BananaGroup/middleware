#include <Time.h>

int externalPin = 2;
int corePin = 3;
int extremitiesPin = 4;

int indicatorGround = A5;
int heatIndicator = 10;
int serialIndicator = 11;

int incomingByte = 0;

void setup() {
  
  Serial.begin(9600);
  Serial.flush();
  
  pinMode(serialIndicator, OUTPUT);
  pinMode(heatIndicator, OUTPUT);
  pinMode(indicatorGround, OUTPUT);
  
  digitalWrite(indicatorGround, LOW); // set as ground
}

void loop() {
  
  incomingByte = Serial.read();
  
  if(incomingByte != -1){
    digitalWrite(heatIndicator, HIGH);
  }
  
  digitalWrite(serialIndicator, HIGH);

  float externalTemp = analogRead(externalPin)*(3.3/1024.0);
  float coreTemp = analogRead(corePin)*(3.3/1024.0);
  float extremitiesTemp = analogRead(extremitiesPin)*(3.3/1024.0);

  char externalTempChar[10];
  String externalTempString;
  dtostrf(externalTemp,1,2,externalTempChar);
  externalTempString = String(externalTempChar);

  char coreTempChar[10];
  String coreTempString;
  dtostrf(externalTemp,1,2,coreTempChar);
  coreTempString = String(coreTempChar);

  char extremitiesTempChar[10];
  String extremitiesTempString;
  dtostrf(extremitiesTemp,1,2,extremitiesTempChar);
  extremitiesTempString = String(extremitiesTempChar);


  String json = "{\"user_id\": 1,";
  json = json + "\"readings\": [";
  // s01
  json = json + "{\"sensor_id\" : \"1\",";
  json = json + "\"value\" :";
  json = json + externalTempString;
  json = json + "},";
  //s02
  json = json + "{\"sensor_id\" : \"2\",";
  json = json + "\"value\" :";
  json = json + coreTempString;
  json = json + "},";
  //s03
  json = json + "{\"sensor_id\" : \"3\",";
  json = json + "\"value\" :";
  json = json + extremitiesTempString;
  json = json + "}";
  // and timestamps and close json
  json = json + "], \"timestamp\": false";
  json = json + "}";

  Serial.println(json);
  
  digitalWrite(serialIndicator, LOW);
  
  Serial.flush();
  
  delay(10000);
}
