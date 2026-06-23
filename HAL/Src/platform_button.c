#include "platform_button.h"
#include "mcu_gpio.h"
#include <stdbool.h>

static uint8_t btn_state[4] = {0, 0, 0, 0};

void Platform_Button_Init(void) {
    for (int i = 0; i < 4; i++) {
        btn_state[i] = 0;
    }
}
bool Platform_Button_IsPressed(uint8_t btn_id) {
    uint8_t raw = MCU_GPIO_ReadButton(btn_id);
    bool result = false;
    switch (btn_state[btn_id]) {
        case 0: if (raw == 0) btn_state[btn_id] = 1; break;
        case 1: if (raw == 1) { btn_state[btn_id] = 0; result = true; } break;
    }
    return result;
}
