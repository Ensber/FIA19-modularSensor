#include <SPI.h>
#include "modulstructure.h"

#define _MDEBUG  0
#define _MNORMAL 1

#define _SMCHECKTIMER  0x01
#define _SMREQUESTID   0x02
#define _SMREQUESTDATA 0x03
#define _SMEND         0x04

//SPI-Commands
#define _SLAVESENDDATA     0x00
#define _REQUESTSENSORID   0x01
#define _REQUESTSENSORDATA 0x02

//SHIFT-Register
#define SER   16
#define CLK   0
#define SRCLK 2

//***********************CONFIG******************************
#define _BOUDRADE 115200
#define _DEBUGTRIGGERPIN 5
#define _RUNMODE _MDEBUG

//***********************GLOBAL VARS**************************
uint8_t gCurrentState;
tsModul gModule[_MAXMODULS];

//***********************TOOLS********************************
#if _RUNMODE == _MDEBUG
#endif //_RUNMODE == _MDEBUG

void logLine( char* p_logString )
{
    Serial.println(p_logString);
}

bool isResievedSensorIDsEqual( tuSensorID* p_pSensorId, tuSensorID* p_pSensorId2, uint8_t p_size )
{
    for( uint8_t i = 0; i < p_size; i++ )
    {
        //Serial.print("Compare: "); Serial.print(p_pSensorId[i].data16); Serial.print(" "); Serial.print(p_pSensorId2[i].data16);
        if( p_pSensorId[i].data16 != p_pSensorId2[i].data16 )
        {
            return false;
        } 
    }
    return true;
}

void errorOccoured()
{

}

void selectShiftRegister(uint8_t index) {
    for (int i=0;i<8;i++) {
        digitalWrite(SER, i == index);
        digitalWrite(CLK, HIGH);
        digitalWrite(CLK, LOW);
    }
    digitalWrite(SRCLK, HIGH);
    digitalWrite(SRCLK, LOW);
    //RESET LED
    digitalWrite(SER, HIGH);
    digitalWrite(CLK, HIGH);
    digitalWrite(SRCLK, HIGH);
}

//***********************STATE-MACHINE*************************
void stateMachine()
{
    switch (gCurrentState)
    {
    case _SMCHECKTIMER:
        //do something
        break;
    case _SMREQUESTID:
        //do something
        logLine("request id from modul");
        SPI.transfer(_REQUESTSENSORID);
        delay(1000);

        tuSensorID spibuffer[_MAXMODULTYPES];
        for( uint8_t i = 0; i < _MAXMODULTYPES; i++ )
        {
            spibuffer[i].data16 = 0;
        }
        SPI.transfer(spibuffer, 20);
        logLine("resieve data: ");
        for(uint8_t i = 0; i < _MAXMODULTYPES; i++)
        {
            Serial.print(spibuffer[i].data16);
            Serial.print(", ");
        }
        logLine("");
        if( !isResievedSensorIDsEqual(gModule[0].modulData.sensorId, spibuffer, _MAXMODULTYPES) )
        {
            for(uint8_t i = 0; i < _MAXMODULTYPES; i++)
            {
                gModule[0].modulData.sensorId[i].data16 = spibuffer[i].data16;
            }
        }
        else
        {
            #if _RUNMODE != _MDEBUG
            gCurrentState = _SMREQUESTDATA;
            #endif //_RUNMODE != _MDEBUG
            logLine("data are equal!");
        }
        //gModule[0]->modulData = spibuffer;
        break;
    case _SMREQUESTDATA:
        //do something
        logLine("request data from modul");
        SPI.transfer(_REQUESTSENSORDATA);
        delay(10000);

        tuSensorData spiData[_MAXMODULTYPES];
        for( uint8_t i = 0; i < _MAXMODULTYPES; i++ )
        {
            spiData[i].data = 0;
        }
        SPI.transfer(spiData, 8*_MAXMODULTYPES);
        logLine("resieve data: ");
        for(uint8_t i = 0; i < _MAXMODULTYPES; i++)
        {
            Serial.print(spiData[i].data);
            Serial.print(", ");
        }
        logLine("");
        #if _RUNMODE != _MDEBUG
        gCurrentState = _SMEND;
        #endif //_RUNMODE != _MDEBUG
        break;   
    case _SMEND:
        //do something
        gCurrentState = _SMCHECKTIMER;
        break;
    }
}


//***********************SETUP / LOOP**************************

void setup()
{
    #if _RUNMODE == _MDEBUG
    pinMode(5, INPUT_PULLUP);
    #endif //_RUNMODE == _MDEBUG
    pinMode(SER, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
    selectShiftRegister(-1);
    
    gCurrentState = _SMCHECKTIMER;

    Serial.begin(_BOUDRADE);
    while(!Serial){}
    logLine("Begin Sketch");
    SPI.begin();

}

void loop()
{
    #if _RUNMODE == _MDEBUG
    while( digitalRead(5) == HIGH ){ delay(100); }
    while( digitalRead(5) == LOW ){ delay(100); }
    gCurrentState++;
    #endif //_RUNMODE == _MDEBUG

    stateMachine();
}