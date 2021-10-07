#ifndef SPICOMMUNICATION_H
#define SPICOMMUNICATION_H

#include "SPI.h"

class SPICommunication_c : private SPIClass
{
public:
    void initCom( bool p_isMaster );
    void sendData( uint16_t p_pData, unsigned int p_size );

    bool canInitCom();

private:
    bool m_canInitCom = false;

};

#endif //SPICOMMUNICATION_H