#include "command_controller.h"

CommandController_c::CommandController_c( SPIClass* p_pSPICom )
{
    m_spiCommunication = p_pSPICom;
} 

void CommandController_c::setSensorModul( uint8_t p_number )
{
    
}

void CommandController_c::requestSensorTypeID()
{

}

void CommandController_c::requestSensorData()
{

}

void CommandController_c::requestIfModulHaveDataToSend()
{

}
