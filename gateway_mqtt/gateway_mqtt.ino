// This example uses an Arduino Yun or a Yun-Shield
// and the MQTTClient to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <Bridge.h>
#include <BridgeClient.h>
#include <MQTTClient.h>
#include <Console.h>
#include "SX1276.h"

#define LORA_MODE 4
#define LORA_CHANNEL CH_10_868
#define LORA_POWER 'H'
#define LORA_ADDR 8
#define TOPIC "textTopic"

BridgeClient net;
MQTTClient client;

unsigned long lastMillis = 0;


void initLoRa(){
  
  sx1276.ON();
  Console.println("LoRa On");
  sx1276.setMode(LORA_MODE);
  Console.print("loRa setMode : ");
  Console.println(LORA_MODE);
  sx1276.setChannel(CH_10_868);
  Console.print("loRa setChannel : ");
  Console.println(CH_10_868);
  sx1276.setPower(LORA_POWER);
  Console.print("loRa setPower : ");
  Console.println(LORA_POWER);
  sx1276.setNodeAddress(LORA_ADDR);
  Console.print("loRa set node address : ");
  Console.println(LORA_ADDR);
  Console.println("*********************************\n");
  Console.println("SX1276 successfully configured \n\n");
}

boolean availablePacket(){
 
   sx1276.receivePacketTimeout(10000);
   String p = sx1276.getPacketRecu();
   if(p.length()>0){ 
    return true;
     //sendDonnees(paquet);
     //Console.println("paquet envoye avec succes");
   }
   return false;
}


/*void messageReceived(String &topic, String &payload) {
  Console.println("incoming: " + topic + " - " + payload);
}*/

void setup() {
  Bridge.begin(115200);
  Console.begin();
   while (!Console) ;
  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
    // Print a start message
  Console.println("SX1276 module loRa Configuration\n\n");
  Console.println("*********************************\n");
 
  
  //client.onMessage(messageReceived);

  //connect();
   initLoRa();
}

void loop() {
  if(availablePacket()){
      String payload = sx1276.getPacketRecu();
      Console.println(payload);
       //client.begin("10.130.1.200", 1883, net);
    //if (!client.connected())
    //  client.connect("arduino", "try", "try");
    //client.publish("/hello", payload);
   }
  
 // client.loop();

  //if (!client.connected()) {
  //  connect();
  //}

  // publish a message roughly every second.
  //if (millis() - lastMillis > 1000) {
  //  lastMillis = millis();
   
  //}
}
