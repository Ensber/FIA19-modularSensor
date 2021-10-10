#include "spicommunication.h"
#include "command_controller.h"

SPICommunication_c* spiCom;
CommandController_c* cmdCtrl;
byte buff[50];
byte reset=0;

void log(char* msg);

void setup() {
   Serial.begin(9600);

   spiCom = new SPICommunication_c;
   spiCom->initCom();   
   cmdCtrl = new CommandController_c(spiCom);

   reset=0xFF;
}


void loop() {
  if( spiCom->canInitCom() )
  {
    int32_t test = 273409;
    //spiCom->sendData( &test, 4 );
    cmdCtrl->requestSensorTypeID();
    Serial.print("response: "); Serial.println(*spiCom->getLastResponse(), HEX);
    
    
    delay(1000);

    /* Todo
    - vector uint8_t
    - größe immer 256 byte (der Vector insgesammt) freier Speicher
    - falls sensor 256 byte sendet, dann sollen diese verfügbar sein!
    - loop durch sensor und dessen Responsedaten in den vector schreiben
    */
    
    
    //spiCom->sendData( &reset, 1 );
    log("gesendet");
  }
  delay(5000);
}

void log(char* msg)
{
  Serial.println(msg);
}