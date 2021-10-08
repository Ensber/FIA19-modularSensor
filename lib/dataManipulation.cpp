#include "dataManipulation.hpp"

uint16_t dataManipulation::LoRaLongSend(std::vector<uint8_t>* packet, uint16_t index) {
    if (LoRa.beginPacket()) {
        for (uint16_t i=index; i<min(index+255, (int)packet->size()); i++) {
            LoRa.write(packet->at(i));
        }
        LoRa.endPacket();
        return index+255;
    } else {
        return index;
    }
}

// returns size of packet
uint16_t dataManipulation::LoRaLongReceive(std::vector<uint8_t>* packet) {
    uint16_t packetSite = LoRa.parsePacket();
    if (packetSite) {
        // resize packet
        packet->reserve(packet->size() + packetSite);

        while (LoRa.available()) {
            packet->push_back(LoRa.read());
        }

        return this->decodePacketHeader(packet).decoded.size;
    }
}