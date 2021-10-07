#include "spicommunication.h"

SPICommunication_c* spiCom;
uint16 buff=1;

void log(char* msg);

void setup() {
   Serial.begin(9600);

   spiCom = new SPICommunication_c;
   spiCom->initCom(true);
}


void loop() {
  if( spiCom->canInitCom() )
  {
    spiCom->sendData( buff, sizeof buff );
    log("gesendet");
  }
  delay(5000);
}

void log(char* msg)
{
  Serial.println(msg);
}