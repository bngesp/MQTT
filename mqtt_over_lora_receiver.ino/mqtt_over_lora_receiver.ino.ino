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
#define LORA_ADDR 8


void initLoRa(){
  
  sx1276.ON();
  Serial.println("LoRa On");
  sx1276.setMode(LORA_MODE);
  Serial.print("loRa setMode : ");
  Serial.println(LORA_MODE);
  sx1276.setChannel(CH_10_868);
  Serial.print("loRa setChannel : ");
  Serial.println(CH_10_868);
  sx1276.setPower(LORA_POWER);
  Serial.print("loRa setPower : ");
  Serial.println(LORA_POWER);
  sx1276.setNodeAddress(LORA_ADDR);
  Serial.print("loRa set node address : ");
  Serial.println(LORA_ADDR);
  Serial.println("*********************************\n");
  Serial.println("SX1276 successfully configured s\n\n");
}

String listenPacket(){
  String paquet = "";
  paquet = sx1276.getPacketRecu();
  //for(unsigned int i=0; i<sx1276._payloadlength; i++)
  //  Serial.print((char)sx1276.packet_received.data[i]);
  return paquet;
  
}


boolean availablePacket(){
 
   sx1276.receivePacketTimeout(10000);
   String p = sx1276.getPacketRecu();
   if(p.length()>0){ 
    return true;
     //sendDonnees(paquet);
     //Serial.println("paquet envoye avec succes");
   }
   return false;
}

void setup()
{
   Serial.begin(115200);
  
  // Print a start message
  Serial.println("SX1276 module loRa Configuration\n\n");
  Serial.println("*********************************\n");
  initLoRa();
}

void loop()
{
  //String packet= listenPacket();
  if(availablePacket())
    Serial.println(sx1276.getPacketRecu());
}
