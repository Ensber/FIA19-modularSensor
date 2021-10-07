#include "SPI.h"

class SPICommunication_c
{
public:
    void startCom();
    void sendData( char* p_data );

private:
    char* m_dataToSend;
}