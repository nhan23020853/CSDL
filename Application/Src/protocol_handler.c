#include "protocol_handler.h"
#include "comm.h"
#include <string.h>

void Protocol_SendTelemetry(float rpm, float kp, float ki, float kd) {
    FrameType_t tx;
    tx.SOF = SOF_BYTE;
    tx.Type_GID = (0x02 << 4) | 0x01;
    tx.ID = 0x21;
    tx.len = 16;

    memcpy(&tx.payload[0], &rpm, 4);
    memcpy(&tx.payload[4], &kp, 4);
    memcpy(&tx.payload[8], &ki, 4);
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
