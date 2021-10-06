#include "SPI.h"
char buff[]="Hello Slave\r\n";

void setup() {
   Serial.begin(9600);
   SPI.begin();
}


void loop() {
 Serial.println("Send String: " + String(buff) );
 for(int i=0; i<sizeof buff; i++)
 {
   SPI.transfer(buff[i]);
 }
 delay(1000);  
}