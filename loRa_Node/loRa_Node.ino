#include "SX1276.h"
#include <SPI.h>
#define LORA_GATEWAY 8

#define LORA_MODE 4
#define LORA_CHANNEL CH_10_868
#define LORA_POWER 'H'
#define LORA_ADDR 3


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

void sendDonnees(String paquet){
  Serial.println(paquet.length());
  char buff[paquet.length()+1];
  paquet.toCharArray(buff, paquet.length()+1); 
  sx1276.sendPacketTimeout(LORA_GATEWAY, buff);
  Serial.print("Packet sent, state ");
  //Serial.println(e, DEC);
  Serial.println(strlen(buff));
  delay(5000);
}


void setup()
{
   Serial.begin(115200);
  
  // Print a start message
  Serial.println("SX1276 module loRa Configuration\n\n");
  Serial.println("*********************************\n");
  initLoRa();
}


void loop(){

  String data = "voici kelk donnees";
  sendDonnees(data);
}


