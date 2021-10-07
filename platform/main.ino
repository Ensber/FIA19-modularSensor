#include "spicommunication.h"

SPICommunication_c* spiCom;
uint8_t buff=15;

void log(char* msg);

void setup() {
   Serial.begin(9600);

   spiCom = new SPICommunication_c;
   spiCom->initCom();
}


void loop() {
  if( spiCom->canInitCom() )
  {
    spiCom->sendData( buff, sizeof buff );
    Serial.print("resieve "); Serial.println(spiCom->getLastRecievedByte());
    log("gesendet");
  }
  delay(5000);
}

void log(char* msg)
{
  Serial.println(msg);
}