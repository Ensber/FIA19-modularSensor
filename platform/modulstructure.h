#ifndef MODULSTRUCTURE_H
#define MODULSTRUCTURE_H

#include <vector>

#define __PACKED __attribute__((packed))
#define _MAXMODULTYPES 10
#define _MAXMODULS     6

typedef union __PACKED _tuSensorID
{
    uint16_t data16;
    uint8_t data8[2];
} tuSensorID;

typedef union __PACKED _tuSensorData
{
    double data;
    uint64_t data64;
    uint32_t data32[2];
    uint16_t data16[4];
    uint8_t data8[8];
} tuSensorData;

typedef struct _tsModulData
{
    tuSensorID sensorId[_MAXMODULTYPES];
    tuSensorData sensorData[_MAXMODULTYPES];
} tsModulData;

typedef struct _tsModul
{
    tsModulData modulData;
    uint8_t chipSelect;
} tsModul;

#endif //MODULSTRUTURE_H