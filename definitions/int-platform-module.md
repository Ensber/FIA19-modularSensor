# Interface communication for the platform and a module

## common bus definition

| Pin | Function |
|-----|----------|
| 1   | 5V       |
| 2   | 3.3V     |
| 3   | MOSI     |
| 4   | MISO     |
| 5   | CS       |

The detectpin is shorted to the CS pin on the module side

## protocol definition

Table is in the point of view of the platform (SPI Master)

| cmd    | request definition                   | response definition                                    | request format                     | response format              |
|--------|--------------------------------------|--------------------------------------------------------|------------------------------------|------------------------------|
| `0x01` | get the sensor type-id               | sensor metadata package                                | `0x01`                             | {16Bit - Sensor ID}          |
| `0x02` | get sensor reading                   | reading data package                                   | `0x02`                             | {8Bit package size}{package} |
| `0x10` | ask module for request               | return if module is done or wants to request something | `0x10`                             | `0x01` or `0x00`             |
| `0x11` | let module send a request            | send request to platform                               | `0x11`                             | {8Bit package size}{package} |
| `0x12` | response for module request          |                                                        | `0x12`{8Bit package size}{package} |                              |


## flow

| step | flow | data   | description                    |
|------|------|--------|--------------------------------|
| 1    | M->S | `0x01` | get sensor ID                  |
| 2    | S->M | PACKET | sensor ID                      |
| 3    | M->S | `0x10` | check for request              |
| 4    | S->M | BOOL   | if false: goto step 9          |
| 5    | M->S | `0x11` | let module send a request      |
| 6    | S->M | PACKET | request pacet to parse and run |
| 7    | M->S | PACKET | response to request            |
| 8    |      |        | goto step 3                    |
| 9    | M->S | `0x02` | get sensor value               |
| 10   | S->M | PACKET | sensor value                   |