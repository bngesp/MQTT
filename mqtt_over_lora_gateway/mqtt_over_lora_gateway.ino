/*
 * mqtt_over_lora_gateway.ino
 *
 *  Created on: 05 Aout 2018
 *      Author: Bassirou NGOM 
 */  

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "SX1276.h"

#define LORA_MODE 4
#define LORA_CHANNEL CH_10_868
#define LORA_POWER 'H'
#define LORA_ADDR 1


byte mac[]    = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 227);
IPAddress server(192, 168, 0, 226);
void initLoRa(){
  sx1276.ON();
  sx1276.setMode(LORA_MODE);
  sx1276.setChannel(LORA_CHANNEL);
  sx1276.setPower(LORA_POWER);
  sx1276.setNodeAddress(LORA_ADDR);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
String payload= "hello world ";
EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //payload+=counter++;
      //char buff[payload.length()];
      //payload.toCharArray(buff,payload.length());
      Serial.println("sending first msg to broker");
      client.publish("outTopic", "first msg");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  
  
  }
}

void setup()
{
  Serial.begin(57600);

  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }else{
     //payload+=counter++;
  char buff[payload.length()];
  //payload.toCharArray(buff,payload.length());
  Serial.println("sending msg to broker");
  client.publish("outTopic", buff);
  delay(5000);
  }
  
  client.loop();
}
