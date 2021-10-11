#include "lora-com.h"

/*
STATE LOOKUP
  0 - Initial state / idle

 10 - Init collect new macs
 11 - Send Request to get macs
 12 - 3 ch receive macs
 13 - 3 ch max ack macs

 20 - Init request data
 21 - Request data from platform
 22 - receive data from platform
 23 - decode data from platform
 24 - send ack and config data
*/

bool lora_manager_class::setState(int state) {
    if ((state % 10) == 0 && (this->state % 10) == 0) {
        this->state = state;
        this->isIdle = state > 0;
        return true;
    }
    return false;
}

void lora_manager_class::run() {
    switch (this->state) {

        // ####################     idle     #################### //

        case 0: // Initial state / idle
            this->isIdle = true;
        break;

        // #################### collect macs #################### //

        case 10: // Init collect new macs
            this->state = 11;
            // setup array to include letter "L"
            this->data.clear();
            this->data.resize(1);
            this->data[0] = 'L';
            this->attempts = 0;
            this->index = 0;
        break;
        case 11: // Send Request to get macs
            this->dataManipulation.LoRaLongSend(&this->data, this->index, false);
            Serial.println("Send request to get macs of orphans");
            this->state = 12;
            this->dataManipulation.reset();
            this->data.clear();
        break;
        case 12: // 3 ch receive macs
            this->info = this->dataManipulation.LoRaLongReceive(&this->data);
            if (
                    (info.decoded.size != 7 && info.decoded.size != 0) ||
                    this->dataManipulation.err_timeout ||
                    this->dataManipulation.err_hashMissmatch ||
                    (this->dataManipulation.transmissionFinished && this->data[10] != 'l')
                ) {
                Serial.println("Failed attempt");
                this->attempts++;
                this->dataManipulation.reset();
                this->data.clear();
            } else if (this->dataManipulation.transmissionFinished) {
                for (int i=0;i<6;i++) 
                    this->currentMac[this->macCount][i] = this->data[i+11];
                Serial.println("Recieved a new mac");
                this->macCount++;
                this->attempts++;
                this->dataManipulation.reset();
                this->data.clear();
            }
            if (this->attempts == 4 || this->macCount == 3) {
                this->state = 13;
            }
        break;
        case 13: // 3 ch max ack macs
        {
            Serial.println("Broadcasting ACKs...");
            this->data.clear();
            this->dataManipulation.reset();
            this->data.resize(7);
            this->data[0] = 'A'; // ACK
            for (int i=0; i<this->macCount; i++) {
                // copy mac into data
                for (int j=0; j<6;j++) this->data[j+1] = this->currentMac[i][j];
                // send ACK for mac
                this->index = 0;
                this->dataManipulation.LoRaLongSend(&this->data, this->index, false);
            }
            this->state = 0;
            Serial.println("Broadcasted ACK for mac addresses");

            // plug new macs into mac table
            for (int i=0;i<this->macCount;i++) {
                bool found = false;
                for (int j=0;j<this->platformRegister.size();j++) {
                    bool missmatch = false;
                    for (int k=0;k<6;k++) 
                        missmatch |= this->platformRegister[j].mac[k] != this->currentMac[i][k];
                    // if found
                    if (!missmatch) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    platformEntry entry;
                    for (int j=0;j<6;j++) entry.mac[j] = this->currentMac[i][j];
                    entry.notSyncedWithWebServer = true;
                    entry.nextRequestTime = -1; // dont request
                    this->platformRegister.push_back(entry);
                }
            }

            for (int i=0;i<this->platformRegister.size();i++) {
                Serial.println(String("PLATFORM - ") + i);
                for (int j=0;j<6;j++) {
                    Serial.print(" -> ");
                    Serial.println((int)this->platformRegister[i].mac[j]);
                }
            }

            this->macCount = 0;
            this->data.clear();
            delay(5000);
        }
        break;

        // #################### collect data #################### //

        case 20: // Init request data
            this->macCursor = -1;
            this->state = 21;
        break;
        case 21: // Request data from platform

            // increment cursor
            this->macCursor++;
            if (this->macCursor == this->platformRegister.size()) {
                this->state = 0;
                return;
            }

            // broadcast request for plattform reading
            this->data.clear();
            this->data.resize(7);
            for (int i=0;i<6;i++) {
                this->data[i+1] = this->platformRegister[this->macCursor].mac[i];
            }
            this->data[0] == 'R';
            // Serial.println(String("SEND A: ") + this->dataManipulation.LoRaLongSend(&this->data, this->index, false));
            this->data.clear();
            this->state = 22;
        break;
        case 22: // receive data from platform
            this->info = this->dataManipulation.LoRaLongReceive(&this->data);
            if (
                this->dataManipulation.err_timeout ||
                this->dataManipulation.err_hashMissmatch ||
                (this->dataManipulation.transmissionFinished && this->data[10] != 'F')
            ) {
                Serial.println("plattform unreachable");
                this->dataManipulation.reset();
                this->data.clear();
                this->state = 21;
            } else if (this->dataManipulation.transmissionFinished){
                Serial.println("Recieved a plattform frame");
                this->dataManipulation.reset();
                this->state = 23;
            }
        break;
        case 23: // decode data from platform

            // send data to WS and get response
            // this->data.clear();
            this->state = 24;
            this->index = 0;
        break;
        case 24: // send ack and config data
            this->index = this->dataManipulation.LoRaLongSend(&this->data, this->index, this->responseHasManagementFrame);
            if (this->dataManipulation.transmissionFinished) {
                this->state = 21;
            }
        break;
        default:
        break;
    }
}