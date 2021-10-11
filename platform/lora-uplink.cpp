#include <ESP8266WiFi.h> // to get mac address
#include "lora-uplink.h"

/*
STATE LOOKUP
  0 - Initial State / idle / waiting for commands

 10 - [->L] Register mac address at station
 11 - [->A] Check mac ack signal

 20 - [->R] Send sensor readings
 21 - [EXT] Run readings function
 22 - send readings
 23 - [->M] parse management frame
*/

void lora_uplink_class::run() {
    bool clearRecvBuffer = false;
    uint8_t mac[6];

    switch(this->state) {

        // ####################     idle     #################### //

        case 0: // Initial State / idle / waiting for commands
            this->cCommand = 0;
            this->info = this->dataManipulation.LoRaLongReceive(&this->data);
            if (this->dataManipulation.err_timeout || this->dataManipulation.err_hashMissmatch) {
                Serial.println("Failed attempt");
                this->dataManipulation.reset();
                this->data.clear();
            } else if (this->dataManipulation.transmissionFinished) {
                Serial.println("Recieved a new command");
                this->cCommand = this->data[10];

                // jump to referenced state
                clearRecvBuffer = true;
                
                switch (this->cCommand) {
                    case 'L': this->state = 10; break; // request to transmit mac
                    case 'A': this->state = 11; break; // ack for mac
                    case 'R': this->state = 20; break; // request to 
                    case 'M': this->state = 23; break; // parse management frame
                    default:
                        Serial.print  (String("unknown command '") + cCommand + "'");
                        Serial.println((int)cCommand);
                    break;
                }
            }
        break;

        // #################### mac register #################### //

        case 10: // [->L] Register mac address at station

            // dont spam the register, aka only register once
            if (this->isRegistered) break;

            // delay to get into one of three slots
            delay(this->dataManipulation.timeout * (LoRa.random() % 3));

            this->index = 0;
            this->data.clear();
            this->data.resize(7);
            this->data[0] = 'l';

            WiFi.macAddress(mac);
            for (int i=0;i<6;i++) this->data[i+1] = mac[i];
            this->dataManipulation.LoRaLongSend(&this->data, this->index, false);

            this->state = 0;
        break;
        case 11: // [->A] Check mac ack signal
        {
            bool missmatch = false;
            WiFi.macAddress(mac);
            for (int i=0;i<6;i++) missmatch |= this->data[11+i] != mac[i];
            this->isRegistered |= !missmatch;

            this->state = 0;
        }
        break;

        // ####################     idle     #################### //

        case 20: // [->R] Send sensor readings
            bool missmatch = false;
            WiFi.macAddress(mac);
            for (int i=0;i<6;i++) missmatch |= this->data[11+i] != mac[i];
            this->data.clear();
            if (missmatch) {
                Serial.println("Ignoring request for data (not for me)");
                this->state = 0;
            } else {
                Serial.println("Request for data recieved!");
                this->data.push_back('F');
                this->index = 0;
                this->dataManipulation.reset();
                this->state = 21;
            }
        break;
        case 21: // Run readings function                               / STATE_WAITING_FOR_SENSOR_DATA
            // set the data in the outside code and set the state to 22 / STATE_SEND_SENSOR_DATA
            this->data.reserve(256);
            for (int i=0;i<255;i++) this->data.push_back('A' + (i%26));
            this->state = 22;
        break;
        case 22: // send readings
            this->dataManipulation.LoRaLongSend(&this->data, this->index, false);
            if (this->dataManipulation.transmissionFinished) {
                this->dataManipulation.reset();
                this->data.clear();
                this->state = 0;
            }
        break;
        case 23: // [->M] Wait for management frame
            this->info = this->dataManipulation.LoRaLongReceive(&this->data);
            if (this->dataManipulation.err_timeout || this->dataManipulation.err_hashMissmatch) {
                Serial.println("Failed attempt (management frame)");
                this->dataManipulation.reset();
                this->data.clear();
                // maby reset on a corrupted management frame to relogin and regain another management frame?
            } else if (this->dataManipulation.transmissionFinished) {
                Serial.println("Recieved a new command");
                this->state = 24;
            }
        break;
        case 24: // parse management frame
            // TODO: parse
            Serial.println("I recieved a management frame, but since it is a supid ass frame, I elected to ignore it");
            this->data.clear();
            this->dataManipulation.reset();
            this->state = 0;
        break;
    }
    if (clearRecvBuffer) {
        this->dataManipulation.reset();
        this->data.clear();
    }
}