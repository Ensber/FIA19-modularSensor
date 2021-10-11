#include "lora-com.h"
// #include "lib/lora/lora.h"
#include "lib/lora/datamanipulation.h"
#include "lib/lora/dataManipulation.cpp"

#include <vector>

lora_manager_class lora_manager;
data_manipulation_class data_manipulation;

std::vector<uint8_t> testPayload;

void setup() {
    Serial.begin(115200);
    Serial.println("TESTT");

    LoRa.setPins(15, 5, 4);
    LoRa.begin(433E6);
    LoRa.setSpreadingFactor(7);
    LoRa.setSignalBandwidth(250e3);
    LoRa.disableCrc();

    uint16_t payloadLen = 1024;
    testPayload.resize(payloadLen);
    for (int i=0;i<payloadLen;i++) testPayload[i] = 'A' + (i % 26);

    lora_manager.setState(lora_manager.STATE_COLLECT_NEW);
    lora_manager.dataManipulation.timeout = 1000; // 1s ### DEBUG ###
}

// uint16_t index_ = 0;
// void loop() {
//     // if (LoRa.beginPacket()) {
//     //     Serial.println("SENDING");
//     //     for (int i=0;i<10;i++)
//     //     LoRa.write('A' + i);
//     //     LoRa.endPacket();
//     // }

//     index_ = data_manipulation.LoRaLongSend(&testPayload, index_, false);

//     Serial.println("--");
//     Serial.println((int)index_);
//     Serial.println(testPayload.size());

//     if (index_ == testPayload.size()) {
//         Serial.println("RESET");
//         index_ = 0;
//         delay(1000);
//     }

//     Serial.flush();
//     delay(500);
// }

int lastState = 0;
int masterState = 0;
void loop() {
    if (lastState != lora_manager.state) {
        Serial.println(String("State changed: ") + lastState + " -> " + lora_manager.state);
        lastState = lora_manager.state;
    }
    lora_manager.run();

    if (lora_manager.state == 0) {
        masterState = (masterState + 1) % 2;
        Serial.println("Changed master state");

        if (masterState == 0)
            lora_manager.state = lora_manager.STATE_COLLECT_NEW;

        if (masterState == 1)
            lora_manager.state = lora_manager.STATE_REQUEST_DATA;
    }
}