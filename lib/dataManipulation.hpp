#ifndef DATAMANIPULATION_HPP
#define DATAMANIPULATION_HPP

#include <LoRa.h>
#include <vector>

// 16Bit packet size header
typedef union __attribute__((packet)) fPacketSize {
    uint16_t iNum;
    uint8_t  bytes[2];
    struct {
        uint16_t includesManagementFrame :1;
        uint16_t size                    :15;
    } decoded;
};

class dataManipulation {
    uint16_t LoRaLongSend(std::vector<uint8_t>* packet, uint16_t index);
    uint16_t LoRaLongReceive(std::vector<uint8_t>* packet);

    std::vector<uint8_t>* encodePacket(std::vector<uint8_t>* packet);
    fPacketSize decodePacketHeader(std::vector<uint8_t>* packet);
    std::vector<uint8_t>* decodePacket(std::vector<uint8_t>* packet);

};

#endif