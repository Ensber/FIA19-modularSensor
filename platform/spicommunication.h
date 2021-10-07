#ifndef SPICOMMUNICATION_H
#define SPICOMMUNICATION_H

#include "SPI.h"

class SPICommunication_c : private SPIClass
{
public:
    void initCom();
    void sendData( void* p_pTxData, unsigned int p_size );
    byte getLastRecievedByte();

    bool canInitCom();

private:
    bool m_canInitCom = false;
    byte m_lastRecievedByte = 0;
};

#endif //SPICOMMUNICATION_H