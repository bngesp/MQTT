#include <SPI.h>
#include <PubSubClient.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <Console.h>
#include "SX1276.h"

#define LORA_MODE 4
#define LORA_CHANNEL CH_10_868
#define LORA_POWER 'H'
#define LORA_ADDR 8
#define TOPIC "/textTopic"

IPAddress server(10, 130, 1, 200); //adresse Broker
BridgeClient net;
PubSubClient client(net);

/*void callback(char* topic, byte* payload, unsigned int length) {
  Console.print("Message arrived [");
  Console.print(topic);
  Console.print("] ");
  for (int i=0;i<length;i++) {
    Console.print((char)payload[i]);
  }
  Console.println();
}*/

void reconnect() {
  while (!client.connected()) {
    Console.print("Attempting MQTT connection...");
     if (client.connect("arduinoClient")) {
      Console.println("connected");
      // Once connected, publish an announcement...
      client.publish("/outTopic","hello world");
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Console.print("failed, rc=");
      Console.print(client.state());
      Console.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


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

void setup()
{
  Bridge.begin(115200);
  Console.begin();
   while (!Console) ;
  client.setServer(server, 1883);
  //client.setCallback(callback);
  Console.println("SX1276 module loRa Configuration\n\n");
  Console.println("*********************************\n");
   initLoRa();
   
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }//else{
    if(availablePacket()){
      String payload = sx1276.getPacketRecu();
      Console.println(payload);
      client.publish("/outTopic",sx1276.packet_received.data);
   }
  
  //}
  //client.loop();
}
