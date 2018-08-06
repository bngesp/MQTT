/*
 * mqtt_over_lora_gateway.ino
 *
 *  Created on: 05 Aout 2018
 *      Author: Bassirou NGOM 
 */  

#include <SPI.h>
#include <Ethernet.h>
#include <Console.h>
#include "SX1276.h"



#define LORA_MODE 4
#define LORA_CHANNEL CH_10_868
#define LORA_POWER 'H'
#define LORA_ADDR 8
#define TOPIC "textTopic"

//Client yunClient;

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
  Console.println("SX1276 successfully configured s\n\n");
}

String listenPacket(){
  String paquet = "";
  paquet = sx1276.getPacketRecu();
  //for(unsigned int i=0; i<sx1276._payloadlength; i++)
  //  Console.print((char)sx1276.packet_received.data[i]);
  return paquet;
  
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
  // Console.begin(115200);
  Bridge.begin(115200);
  Console.begin();
  while (!Console) ; 
  // Print a start message
  Console.println("SX1276 module loRa Configuration\n\n");
  Console.println("*********************************\n");
  initLoRa();
}

void loop()
{
  //String packet= listenPacket();
   
    if(availablePacket()){
      String payload = sx1276.getPacketRecu();
      Console.println(payload);
    }
  
  
  //client.loop();
  
    //Console.println();
}
