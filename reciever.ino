#include <SPI.h>
#include <LoRa.h>

void setup() {  
 Serial.begin(9600);

 while (!Serial);

 Serial.println("Sensor de proxomidade receptor");

 if (!LoRa.begin(915E6)) {
  Serial.println("Falha ao iniciar LoRa!");
  while (1);
 }else{
  Serial.println("LoRa iniciado!");
 }
}

void loop() {
 String packet = "";
  
 int packetSize = LoRa.parsePacket();
 if (packetSize) {
  Serial.print("Recebendo pacote: -- ");

  while (LoRa.available()) {
   packet = LoRa.readString();
  }
    
  Serial.println(packet);
  Serial.println();

  int firstcommaIndex   = packet.indexOf(';');
  int secondCommaIndex  = packet.indexOf(';', firstcommaIndex+1);

  String firstValue  =  packet.substring( 0, firstcommaIndex);
  String secondValue =  packet.substring(firstcommaIndex+1, secondCommaIndex);

  Serial.print("Distância:-"); Serial.println(secondValue);
  Serial.println();

  /*Não podemos imprimir o primeiro dígito, pois
  é um valor fictício enviado pela LoRa String
  em caso de perda de transmissão*/

  delay(3000);
 }
}