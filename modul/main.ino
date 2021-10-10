#include "SPI.h"

typedef union __attribute__((packet)) bdouble {
   double number;
   uint8_t data[8];
};

byte buff [255];
volatile byte indx;
volatile boolean byteResieved;
byte testAr[8] = {0,0,0,0,0,0,0,0};
int32_t uilData=0;
uint8_t index=0;
double testd =0;

bdouble test_double = {0.0};

void conv(double d, byte *arr) {
   test_double.data[0];
}

void initSPICom()
{
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   byteResieved = false;
   SPI.attachInterrupt(); // turn on interrupt
}

void spiSend(int8_t p_byteToSend)
{
   SPI.transfer(p_byteToSend);
}

void handleResieve()
{
   byte c = SPDR; // read byte from SPI Data Register
   
   index++;
   uilData=uilData<<8;
   uilData=c;
   Serial.print("resieve: "); Serial.println(c, HEX);   
   if(c==0xFF)
   {
      resetSPIRxBuffer();
      Serial.print("RX reset");
   }
   else if(c==0x01)
   {
      Serial.println("Should send my id..");
      uint8_t id = 0x22;

      
      Serial.print("send:"); Serial.println(id, HEX);  spiSend(0x22);
   }
   /*
   else if(index==4){
      Serial.print("wert:"); Serial.println(uilData);
      resetSPIRxBuffer();
   }
   //test_double.data[indx++] = c;
   
   /*
   if(c == 0x15)
      Serial.println("have resieved 0x15");
   else
   */
}

void resetSPIRxBuffer()
{
   uilData=0;
   index=0;
}

ISR (SPI_STC_vect) // SPI interrupt routine 
{
   handleResieve();
}

//************************************************************************




void setup (void) {
   Serial.begin (9600);
   initSPICom();
}


void loop (void) {
   if (byteResieved) {
      //Serial.println (buff); //print the array on serial monitor
      indx= 0; //reset button to zero
   }
}