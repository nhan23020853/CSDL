#ifndef PLATFORM_BUTTON_H
#define PLATFORM_BUTTON_H

#include <stdint.h>
#include <stdbool.h>

void Platform_Button_Init(void);
bool Platform_Button_IsPressed(uint8_t btn_id);

#endif
