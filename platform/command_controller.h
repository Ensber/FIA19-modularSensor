#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

#include "spicommunication.h"

class CommandController_c
{
public:
    CommandController_c( SPICommunication_c* p_pSPICom );
    void setSensorModul( uint8_t p_modulID );
    void requestSensorTypeID();
    void requestSensorData();
    void requestIfModulHaveDataToSend();
    void letModulSendRequest();
    void responseForModulRequest();

private:

    uint8_t m_cmdGetSensorTypeID = 0x01;
    uint8_t m_cmdGetSensorReading = 0x02;
    uint8_t m_cmdAkModulforRequest = 0x10;
    uint8_t m_cmdLetModuleSendRequest = 0x11;
    uint8_t m_cmdResponseForModuleRequest = 0x12;

    SPICommunication_c* m_spiCommunication;
    uint8_t m_currentModulID = 0;
};

#endif //COMMAND_CONTROLLER_H