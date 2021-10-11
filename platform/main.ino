#ifdef NICLAS_DEV // to prevent errors

#include "spicommunication.h"

SPICommunication_c* spiCom;
byte buff[50];

void log(char* msg);

void setup() {
   Serial.begin(9600);

   spiCom = new SPICommunication_c;
   spiCom->initCom();
}


void loop() {
  if( spiCom->canInitCom() )
  {
    Serial.println("davor");
    buff[0] = 0x15;
    double test = 273409.394;
    Serial.println((int)buff[0]);
    Serial.println("danach");
    spiCom->sendData( buff, sizeof buff );
    Serial.print("resieve "); Serial.println(spiCom->getLastRecievedByte());
    spiCom->sendData( &test, sizeof test );
    log("gesendet");
  }
  delay(5000);
}

void log(char* msg)
{
  Serial.println(msg);
}

#endif