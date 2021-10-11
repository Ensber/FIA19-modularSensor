#ifndef LORA_UPLINK_HPP
#define LORA_UPLINK_HPP

#include <LoRa.h>
#include "lib/lora/lora.h"
#include "lib/lora/datamanipulation.h"

class lora_uplink_class {
    private:

        // generic connection data
        uint16_t index = 0;
        fPacketSize info;
        std::vector<uint8_t> data;
    public:
        int state = 0;
        char cCommand = 0;

        const int STATE_WAITING_FOR_SENSOR_DATA = 21;
        const int STATE_SEND_SENSOR_DATA        = 22;
        
        data_manipulation_class dataManipulation;

        bool isRegistered = false;

        bool setState(int state);
        void run();

};

#endif