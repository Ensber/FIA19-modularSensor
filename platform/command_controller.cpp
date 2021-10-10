#include "command_controller.h"

CommandController_c::CommandController_c( SPICommunication_c* p_pSPICom )
{
    m_spiCommunication = p_pSPICom;
} 

void CommandController_c::setSensorModul( uint8_t p_modulID )
{
    m_currentModulID = p_modulID;
}

void CommandController_c::requestSensorTypeID()
{
    uint8_t response = 0;
    m_spiCommunication->sendData( &m_cmdGetSensorTypeID, sizeof m_cmdGetSensorTypeID, &response );
    //Get Data!
}

void CommandController_c::requestSensorData()
{
    m_spiCommunication->sendData( &m_cmdGetSensorReading, sizeof m_cmdGetSensorTypeID );
}

void CommandController_c::requestIfModulHaveDataToSend()
{
    m_spiCommunication->sendData( &m_cmdAkModulforRequest, sizeof m_cmdGetSensorTypeID );
}

void CommandController_c::letModulSendRequest()
{
    m_spiCommunication->sendData( &m_cmdLetModuleSendRequest, sizeof m_cmdGetSensorTypeID );
}

void CommandController_c::responseForModulRequest()
{
    m_spiCommunication->sendData( &m_cmdResponseForModuleRequest, sizeof m_cmdGetSensorTypeID );
}
