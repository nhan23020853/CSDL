#include "protocol_handler.h"
#include "comm.h"
#include <string.h>

void Protocol_SendTelemetry(float rpm1, float rpm2, float kp, float kd) {
    FrameType_t tx;
    tx.SOF = SOF_BYTE;
    tx.Type_GID = (0x02 << 4) | 0x01;
    tx.ID = 0x21; // ID này cho Python biết là gói Telemetry
    tx.len = 16;  // 4 float * 4 bytes = 16 bytes

    memcpy(&tx.payload[0], &rpm1, 4);
    memcpy(&tx.payload[4], &rpm2, 4);
    memcpy(&tx.payload[8], &kp, 4);
    memcpy(&tx.payload[12], &kd, 4);

    Comm_PushTxFrame(&tx);
}

void Protocol_SendReport(float rpm) {
    FrameType_t tx;
    tx.SOF = SOF_BYTE;
    tx.Type_GID = (0x02 << 4) | 0x01;
    tx.ID = 0x10;
    tx.len = 4;
    memcpy(tx.payload, &rpm, 4);
    Comm_PushTxFrame(&tx);
}
