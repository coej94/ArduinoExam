#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

//WiFi config
const char ssid[] = "HUAWEI P10";
const char password[] = "lortlort";

//Thingspeak config
const unsigned long channel_id = 399381;
const char write_api_key[] = "CLDEBWK4UAHNV5UK";

//WiFi client
WiFiClient client; 


void setup() {
  Serial.begin(9600);
  delay(100);
  
  //Connect to WiFi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  //Show that we are connected!
  Serial.println("Connected!");

  //Connect to ThingSpeak
  ThingSpeak.begin(client);

  //Timestamp
  randomSeed(micros());

}

void loop() {
  // generate random number 1-100
  int rando = random (1, 101);
  Serial.print("Posting " + String(rando) + "to thingspeak");
  ThingSpeak.setField(1,rando);
  ThingSpeak.writeFields(channel_id, write_api_key);

  delay(3000);

}
