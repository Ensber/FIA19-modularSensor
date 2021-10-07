#include "SPI.h"
char buff [50];
volatile byte indx;
volatile boolean process;

void setup (void) {
   Serial.begin (9600);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}

ISR (SPI_STC_vect) // SPI interrupt routine 
{
  //Serial.println("interrupt: ");
  byte c = SPDR; // read byte from SPI Data Register
  if (indx < sizeof buff) {
    buff [indx++] = c; // save data in the next index in the array buff
    //Serial.print("recieve\""); Serial.print(c); Serial.println("\"");
    SPI.transfer(2);
    if (c == '\r') //check for the end of the word
      process = true;
  }
}

void loop (void) {
   if (process) {
      process = false; //reset the process
      Serial.println (buff); //print the array on serial monitor
      indx= 0; //reset button to zero
   }
}
