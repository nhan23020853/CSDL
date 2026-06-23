#ifndef COMM_H
#define COMM_H
#include <stdint.h>
#include <stdbool.h>

#define SOF_BYTE 0xAA
#define MAX_PAYLOAD_SIZE 32

#pragma pack(push, 1)
typedef struct {
    uint8_t SOF;
    uint8_t Type_GID;
    uint8_t ID;
    uint16_t len;
    uint8_t payload[32];
    uint8_t crc_check;
} FrameType_t;
#pragma pack(pop)

#define GET_TYPE(type_gid) ((type_gid) >> 4)

typedef void (*Comm_RxCallback_t)(FrameType_t *frame);

void Comm_RegisterRxCallback(Comm_RxCallback_t cb);
void Comm_ReceiveByte(uint8_t byte);
bool Comm_PushTxFrame(FrameType_t *frame);
void Comm_Process(void);

#endif
