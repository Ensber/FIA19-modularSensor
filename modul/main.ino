#include "SPI.h"

char buff [50];
volatile byte indx;
volatile boolean byteResieved;

void initSPICom()
{
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   byteResieved = false;
   SPI.attachInterrupt(); // turn on interrupt
}

void setup (void) {
   Serial.begin (9600);
   initSPICom();
}

void spiSend(int8_t p_byteToSend)
{
   SPI.transfer(p_byteToSend);
}

void handleResieve()
{
   byte c = SPDR; // read byte from SPI Data Register
   //wann ist denn ein "Datensatz" angekommen
   Serial.println(c);
   spiSend(200);
   
}

ISR (SPI_STC_vect) // SPI interrupt routine 
{
   handleResieve();
}

void loop (void) {
   if (byteResieved) {
      Serial.println (buff); //print the array on serial monitor
      indx= 0; //reset button to zero
   }
}