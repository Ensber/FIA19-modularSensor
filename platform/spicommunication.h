#ifndef SPICOMMUNICATION_H
#define SPICOMMUNICATION_H

#include "SPI.h"

class SPICommunication_c
{
public:
    void initCom();
    void sendData( void* p_pTxData, unsigned int p_size );
    void sendData( void* p_pTxData, unsigned int p_size, void* p_pRxData );
    uint8_t* getLastResponse();
    bool canInitCom();

private:
    uint8_t m_lastResponse;
    bool m_canInitCom = false;
};

#endif //SPICOMMUNICATION_H