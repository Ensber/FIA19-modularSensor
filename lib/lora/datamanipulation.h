#ifndef DATAMANIPULATION_H
#define DATAMANIPULATION_H

#include <LoRa.h>
#include <vector>
// #include "hamming.h"
// #include "hamming.cpp"

#define FRAME_MAXSIZE 255

// 16Bit packet size header
typedef union __attribute__((packet)) fPacketSize {
    uint16_t iNum;
    uint8_t  bytes[2];
    struct {
        uint16_t includesManagementFrame :1;
        uint16_t packetStart             :1;
        uint16_t size                    :14;
    } decoded;
};

typedef union __attribute__((packet)) packetHeader {
    uint8_t data[5];
    struct {
        uint8_t  pkt_cnt;
        uint32_t pkt_hash;
    } decoded;
};

typedef union __attribute__((packet)) byteUnsignedLong {
    uint8_t data[4];
    unsigned long number;
};

struct transmissionStatus {
    uint16_t    currentTransmissionIndex;
    uint8_t     attempt;
    bool        hasManagementFrame;
    fPacketSize header;
};

class data_manipulation_class {
    private:
        unsigned long lastReceiveTime = 0;
        // std::vector<uint8_t> buffer[3];
    public:
        unsigned long timeout = 10000; // 10s
        byteUnsignedLong hash;

        bool err_timeout          = false;
        bool err_hashMissmatch    = false;
        bool transmissionFinished = false;

        unsigned long hashVector(std::vector<uint8_t>* packet, uint16_t begin, uint16_t end);

        uint16_t    LoRaLongSend                     (std::vector<uint8_t>* packet, uint16_t index, bool hasManagementFrame);
        fPacketSize LoRaLongReceive                  (std::vector<uint8_t>* packet);

        // void LoRaTryhardLongSend(std::vector<uint8_t>* packet, struct transmissionStatus* status);
        // void LoRaTryhardLongReceive(std::vector<uint8_t>* packet, struct transmissionStatus* status);

        uint8_t ECC(std::vector<uint8_t>* arr, uint16_t i);
        uint8_t ECC(uint8_t a, uint8_t b, uint8_t c);

        // std::vector<uint8_t>* encodePacket(std::vector<uint8_t>* packet);
        // std::vector<uint8_t>* decodePacket(std::vector<uint8_t>* packet);

        void reset();
};



#endif