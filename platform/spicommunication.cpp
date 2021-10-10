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
}

void SPICommunication_c::sendData( void* p_pTxData, unsigned int p_size, void* p_pRxData )
{
    //digitalWrite(SlaveSelectPin, LOW);  // Select the Slave device
    void* buffer = malloc(p_size);
    memset(buffer, 0, p_size);
    buffer = memcpy(buffer, p_pTxData, p_size);
    SPI.transfer(buffer, p_size);
    delay(1);
    m_lastResponse = 0;
    m_lastResponse = SPI.transfer(0);
    p_pTxData = &m_lastResponse;

    if( (uint8_t)buffer == m_lastResponse )
    {
        Serial.println("delayerror is possible");
    }
}

uint8_t* SPICommunication_c::getLastResponse()
{
    return &m_lastResponse;
}