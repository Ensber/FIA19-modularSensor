#include "datamanipulation.h"

#ifndef DATA_MANIOULATION_CPP
#define DATA_MANIOULATION_CPP

uint8_t data_manipulation_class::ECC(std::vector<uint8_t>* arr, uint16_t i) {
    if (arr->size() < i + 4) {
        return 0;
    }
    uint8_t a = arr->at(i);
    uint8_t b = arr->at(i + 2);
    uint8_t c = arr->at(i + 4);

    return this->ECC(a, b, c);
}


uint8_t data_manipulation_class::ECC(uint8_t a, uint8_t b, uint8_t c) {
    return ((a^b^0xFF)&a) | ((b^c^0xFF)&b) | ((c^a^0xFF)&c);
}

unsigned long data_manipulation_class::hashVector(std::vector<uint8_t>* packet, uint16_t begin, uint16_t end) {
    if (packet->size() < end) return 0;
    unsigned long charset = 0;
    unsigned long state   = 0;

    // Serial.println(String("Items: ") + (int)(end-begin));
    for (int i=0; i< end-begin; i++) {
        charset <<= 8;
        charset |= (unsigned long)packet->at(i+begin);
        if ((i % 4) == 0) {
            state ^= charset;
            charset = 0;

            state ^= 2747636419u;
            state *= 2654435769u;
            state ^= state >> 16;
            state *= 2654435769u;
            state ^= state >> 16;
            state *= 2654435769u;
        }
    }

    state ^= charset;

    state ^= 2747636419u;
    state *= 2654435769u;
    state ^= state >> 16;
    state *= 2654435769u;
    state ^= state >> 16;
    state *= 2654435769u;

    return state;
}

uint16_t data_manipulation_class::LoRaLongSend(std::vector<uint8_t>* packet, uint16_t index, bool hasManagementFrame) {
    if (LoRa.beginPacket()) {
        uint16_t sendData = min(index + FRAME_MAXSIZE - 6 - ((!index) * 4), (int)packet->size());

        // LoRa.write(index >> 8);
        // LoRa.write(index & 256);
        // send header
        fPacketSize fsize;
        fsize.decoded.includesManagementFrame = hasManagementFrame;
        fsize.decoded.size                    = packet->size();
        fsize.decoded.packetStart             = index == 0;
        for (int i=0;i<3;i++)
            LoRa.write(fsize.bytes[0]),
            LoRa.write(fsize.bytes[1]);
        
        // on first packet: send hash
        if (index == 0 ) {
            // sendData -= 4; // TODO: HIER MUSS BEGRENZUNG HIN
            byteUnsignedLong hash;
            hash.number = this->hashVector(packet, 0, packet->size());
            for (int i=0; i<4; i++) LoRa.write(hash.data[i]);
        }

        for (uint16_t i=index; i<sendData; i++) {
            LoRa.write(packet->at(i));
        }
        LoRa.endPacket();

        this->transmissionFinished = sendData == packet->size();
        return sendData;
    } else {
        return index;
    }
}

// returns size of packet
fPacketSize data_manipulation_class::LoRaLongReceive(std::vector<uint8_t>* packet) {
    int packetSize = LoRa.parsePacket();
    bool start = packet->size() == 0;

    // handle timeouts
    if(millis() - this->lastReceiveTime > this->timeout) {
        this->err_timeout = true;
        this->transmissionFinished = true;
    }

    if (packetSize) {
        // keep track of time for timeouts
        this->lastReceiveTime = millis();

        Serial.print  (String("RECV: "));
        Serial.println(packetSize);
        
        // resize packet
        packet->reserve(packet->size() + packetSize);

        // remove header if not in start
        if (!start) for (int i=0;i<6;i++) LoRa.read();

        while (LoRa.available()) {
            int c = LoRa.read();
            packet->push_back(c);
            // Serial.print("  #> ");
            // Serial.println(c, HEX);
        }
        
        fPacketSize fsize;
        // Serial.println("before ecc"); Serial.flush();
        fsize.bytes[0] = ECC(packet, 0);
        fsize.bytes[1] = ECC(packet, 1);

        // reset if the received telegram is not the start
        if (start && !fsize.decoded.packetStart) {
            Serial.println("Not the start of packet");
            Serial.flush();
            packet->clear();
            fPacketSize x;
            return x;
        }

        // get hash
        if (start) {
            for (int i=0; i<4; i++) this->hash.data[i] = packet->at(i + 6);
        }
        
        // on transmission finished (check transmission hash)
        if (fsize.decoded.size != 0 && fsize.decoded.size <= packet->size() - 10) {
            this->transmissionFinished = true;
            this->err_hashMissmatch = this->hash.number != this->hashVector(packet, 10, packet->size());
        }

        // Serial.println("after ecc"); Serial.flush();
        return fsize;
    }
    fPacketSize x;
    return x;
}

void data_manipulation_class::reset() {
    this->hash.number          = 0;
    this->err_hashMissmatch    = false;
    this->err_timeout          = false;
    this->transmissionFinished = false;
    this->lastReceiveTime      = millis();
}

#endif