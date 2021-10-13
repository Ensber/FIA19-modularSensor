#include "SPI.h"

typedef union __attribute__((packet)) bdouble {
   double number;
   uint8_t data[8];
};

byte buff [255];
uint8_t index=0;
uint8_t cntDataToSend = 0;
uint8_t id = 50;
unsigned int b = 0;

bdouble test_double = {0.0};

//info setze doch mal die id zu begin auf was hohes

void conv(double d, byte *arr) {
   test_double.data[0];
}

void initSPICom()
{
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   index = 0; // buffer empty
   cntDataToSend = 0;
   SPI.attachInterrupt(); // turn on interrupt
}

void spiSend(uint8_t p_byteToSend)
{
   Serial.print("try to send:"); Serial.println((uint8_t)p_byteToSend);
   unsigned int size = sizeof p_byteToSend;
   void* buffer = malloc(size);
   memset(buffer, 0, size);
   buffer = memcpy(buffer, &p_byteToSend, size);
   SPI.transfer(buffer, sizeof buffer);
   Serial.print("send:"); Serial.println((uint8_t)buffer);
   Serial.flush();
}

void handleResieve()
{
   byte c = SPDR; // read byte from SPI Data Register
   //Serial.print("resieve: "); Serial.println(c);
   if(c==0x01)
   {
      //Serial.println("Should send my id..");
      //cntDataToSend = 2;
      //id=50;
      spiSend(2);
      b = 0;
      Serial.print("send:"); Serial.println(cntDataToSend);
      Serial.flush();
   }
   else if(c==0x00)
   {      
      if( b >= 2 )
      {
         spiSend(50);
         b++;
      }
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

ISR (SPI_STC_vect) // SPI interrupt routine 
{
   handleResieve();
}

//************************************************************************




void setup (void) {
   Serial.begin (115200);
   while (!Serial){}
   
   initSPICom();
   spiSend(2);
}


void loop (void) {
}