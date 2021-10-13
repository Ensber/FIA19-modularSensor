#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

#include "SPI.h"

class CommandController_c
{
public:
    CommandController_c( SPIClass* p_pSPICom );
    void setSensorModul( uint8_t p_number );
    void requestSensorTypeID();
    void requestSensorData();
    void requestIfModulHaveDataToSend();

private:
    SPIClass* m_spiCommunication;
};

#endif //COMMAND_CONTROLLER_H