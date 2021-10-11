#ifndef LORA_MANAGER_HPP
#define LORA_MANAGER_HPP

#include <LoRa.h>
#include "lib/lora/lora.h"
#include "lib/lora/datamanipulation.h"

struct platformEntry {
    uint8_t  mac[6];
    uint64_t nextRequestTime;
    uint64_t requestTimePeriode;
    bool     notSyncedWithWebServer;
};

class lora_manager_class {
    private:
        int macCount = 0;
        uint8_t currentMac[3][6]; // stores the three received mac addresses or target mac address in first slot

        // generic connection data
        uint16_t index = 0;
        int attempts = 0;
        fPacketSize info;
        std::vector<uint8_t> data;

        // get data request data
        int macCursor = 0;
        bool responseHasManagementFrame = false;
    public:
        int state = 0;

        data_manipulation_class dataManipulation;

        // internal memory
        std::vector<platformEntry> platformRegister;

        // state pointer
        const int STATE_COLLECT_NEW  = 10;
        const int STATE_REQUEST_DATA = 20;

        bool isIdle = true;

        bool setState(int state);
        void run();
};

#endif