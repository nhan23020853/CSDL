#include "comm.h"
#include "mcu_uart.h"
#include "stm32f4xx.h"
#include <stddef.h>

#define QUEUE_SIZE 8

static FrameType_t rx_queue[QUEUE_SIZE];
static volatile uint8_t rx_head = 0, rx_tail = 0, rx_count = 0;

static FrameType_t tx_queue[QUEUE_SIZE];
static volatile uint8_t tx_head = 0, tx_tail = 0, tx_count = 0;

static Comm_RxCallback_t p_RxCallback = NULL;

static uint8_t rx_state = 0;
static FrameType_t temp;
static uint16_t p_idx = 0;

static uint8_t Calc_CRC(FrameType_t *f) {
    uint8_t crc = f->Type_GID ^ f->ID ^ (f->len & 0xFF) ^ (f->len >> 8);
    for (uint16_t i = 0; i < f->len; i++) crc ^= f->payload[i];
    return crc;
}

void Comm_RegisterRxCallback(Comm_RxCallback_t cb) {
	p_RxCallback = cb;
}

void Comm_ReceiveByte(uint8_t byte) {
    switch (rx_state) {
        case 0: // Đợi byte SOF
            if (byte == SOF_BYTE) {
                rx_state = 1;
            }
            break;

        case 1: // Nhận Type_GID
            temp.Type_GID = byte;
            rx_state = 2;
            break;

        case 2: // Nhận ID
            temp.ID = byte;
            rx_state = 3;
            break;

        case 3: // Nhận Byte thấp của len (LSB)
            temp.len = byte;
            rx_state = 4;
            break;

        case 4: // Nhận Byte cao của len (MSB)
            temp.len |= ((uint16_t)byte << 8);
            p_idx = 0; // Reset index trước khi bắt đầu nhận payload

            if (temp.len > MAX_PAYLOAD_SIZE) {
                rx_state = 0;
            } else {
                rx_state = 5;
            }
            break;

        case 5: // Nhận Payload
            temp.payload[p_idx++] = byte;
            if (p_idx >= temp.len) {
                rx_state = 6;
            }
            break;

        case 6: // Nhận CRC và kiểm tra
            temp.crc_check = byte;
            if (Calc_CRC(&temp) == byte) {
                __disable_irq(); // Bảo vệ biến dùng chung trong ngắt
                if (rx_count < QUEUE_SIZE) {
                    rx_queue[rx_head] = temp;
                    rx_head = (rx_head + 1) % QUEUE_SIZE;
                    rx_count++;
                }
                __enable_irq();
            }
            rx_state = 0; // Quay về trạng thái đợi SOF mới
            break;

        default:
            rx_state = 0;
            break;
    }
}

bool Comm_PushTxFrame(FrameType_t *f) {
    if (tx_count >= QUEUE_SIZE) return false;
    f->crc_check = Calc_CRC(f);
    tx_queue[tx_head] = *f;
    tx_head = (tx_head + 1) % QUEUE_SIZE;
    __disable_irq(); tx_count++; __enable_irq();
    return true;
}

void Comm_Process(void) {
    // 1. Xử lý RX Queue
    if (rx_count > 0) {
        FrameType_t f;
        __disable_irq();
        f = rx_queue[rx_tail];
        rx_tail = (rx_tail + 1) % QUEUE_SIZE;
        rx_count--;
        __enable_irq();

        if (p_RxCallback) p_RxCallback(&f);
    }

    // 2. Xử lý TX Queue
    if (tx_count > 0) {
        FrameType_t f;
        __disable_irq();
        f = tx_queue[tx_tail];
        tx_tail = (tx_tail + 1) % QUEUE_SIZE;
        tx_count--;
        __enable_irq();

        // ĐÓNG GÓI LẠI BUFFER TRƯỚC KHI GỬI (FIX LỖI)
        uint8_t tx_buf[MAX_PAYLOAD_SIZE + 6];

        tx_buf[0] = SOF_BYTE;              // Byte 0: Mã SOF
        tx_buf[1] = f.Type_GID;            // Byte 1: Nhóm lệnh
        tx_buf[2] = f.ID;                  // Byte 2: ID thiết bị
        tx_buf[3] = f.len & 0xFF;          // Byte 3: Độ dài LSB
        tx_buf[4] = (f.len >> 8) & 0xFF;   // Byte 4: Độ dài MSB

        // Byte 5 trở đi: Payload
        for(uint16_t i = 0; i < f.len; i++) {
            tx_buf[5 + i] = f.payload[i];
        }

        // Byte cuối cùng: CRC
        tx_buf[5 + f.len] = f.crc_check;

        // Gửi qua UART: 1 SOF + 4 Header + Payload + 1 CRC = 6 + f.len
        MCU_UART_Send(tx_buf, 6 + f.len);
    }
}
