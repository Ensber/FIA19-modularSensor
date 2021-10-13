// #include "lora-uplink.h"

// #include "lib/lora/datamanipulation.h"
// #include "lib/lora/dataManipulation.cpp"

// data_manipulation_class data_manipulation;
// lora_uplink_class lora_uplink;

// void setup() {
//     Serial.begin(115200);
//     Serial.println("TESTT");

//     LoRa.setPins(15, 5, 4);
//     LoRa.begin(433E6);
//     LoRa.setSpreadingFactor(7);
//     LoRa.setSignalBandwidth(250e3);
//     LoRa.disableCrc();

//     lora_uplink.dataManipulation.timeout = 1000; // 1s ### DEBUG ###
// }

// // #define LISTENER
// #ifdef LISTENER
// std::vector<uint8_t> testPayload;

// uint16_t lSize = 0;
// void loop() {
//     fPacketSize info = data_manipulation.LoRaLongReceive(&testPayload);

//     if (lSize != testPayload.size() || data_manipulation.transmissionFinished) {
//         lSize = testPayload.size();
//         // Serial.println(String("Total size  : ") + info.decoded.size);
//         // Serial.println(String("Current size: ") + testPayload.size());

//         // if (testPayload.size()>=10) {
//         //     for (int i=1;i<10;i++){
//         //         Serial.println((char)testPayload[i], HEX);
//         //     }
//         //     Serial.println("<End of Header>");
//         // }
//         if (data_manipulation.transmissionFinished) {
//             // Serial.println("Transmission finished");
//             // Serial.println(String("Hash ERR: ") + data_manipulation.err_hashMissmatch);
//             // Serial.println(String("Timeout : ") + data_manipulation.err_timeout);
//             for (int i=10;i<testPayload.size();i++) Serial.write((char)testPayload[i]);
//             Serial.println();
//             testPayload.clear();
//             data_manipulation.reset();
//         }
//     }
// }

// #else

// int lastState = 0;
// void loop() {
//     if (lastState != lora_uplink.state) {
//         Serial.println(String("State changed: ") + lastState + " -> " + lora_uplink.state);
//         lastState = lora_uplink.state;
//     }
//     lora_uplink.run();
// }
// #endif