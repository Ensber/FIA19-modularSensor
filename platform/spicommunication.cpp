#include "spicommunication.h"

char recieveBuffer [50];
volatile byte bufferIndx;
volatile boolean process;

void SPICommunication_c::initCom()
{
    SPI.begin();
    m_canInitCom = true;
}

bool SPICommunication_c::canInitCom()
{
    return m_canInitCom;
}

void SPICommunication_c::sendData( void* p_pTxData, unsigned int p_size )
{
    //digitalWrite(SlaveSelectPin, LOW);  // Select the Slave device
    SPI.transfer(p_pTxData, p_size);
    delay(1);
    byte returnedValue = SPI.transfer(0);
    m_lastRecievedByte = returnedValue;
}

byte SPICommunication_c::getLastRecievedByte()
{
    return m_lastRecievedByte;
}