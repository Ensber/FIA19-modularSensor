#include "spicommunication.h"

char recieveBuffer [50];
volatile byte bufferIndx;
volatile boolean process;

void SPICommunication_c::initCom( bool p_isMaster )
{
    if( p_isMaster )
    {
        SPI.begin();
        m_canInitCom = true;
    }
    else
    {
        #ifndef ESP8266
        pinMode(MISO, OUTPUT); // have to send on master in so it set as output
        SPCR |= _BV(SPE); // turn on SPI in slave mode
        bufferIndx = 0; // buffer empty
        process = false;
        SPI.attachInterrupt(); // turn on interrupt
        m_canInitCom = true;
        #else
        Serial.println("ERROR: eps8266 borad can not be a slave!!!!");
        #endif
    }
}

#ifndef ESP8266
ISR (SPI_STC_vect) // SPI interrupt routine 
{
  //Serial.println("interrupt: ");
  byte c = SPDR; // read byte from SPI Data Register
  if (bufferIndx < sizeof recieveBuffer) {
    recieveBuffer [bufferIndx++] = c; // save data in the next index in the array buff
    //Serial.print("recieve\""); Serial.print(c); Serial.println("\"");
    if (c == '\r') //check for the end of the word
      process = true;
  }
}
#endif

bool SPICommunication_c::canInitCom()
{
    return m_canInitCom;
}

void SPICommunication_c::sendData( uint16_t p_pData, unsigned int p_size )
{
    //digitalWrite(SlaveSelectPin, LOW);  // Select the Slave device
    SPI.transfer(p_pData);
    byte returnedValue = SPI.transfer(0);
    Serial.println(returnedValue);
}