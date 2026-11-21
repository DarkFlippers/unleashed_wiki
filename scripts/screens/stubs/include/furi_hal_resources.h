#pragma once
/* host stub: subset of targets/f7/furi_hal/furi_hal_resources.h */
#include <furi_hal_gpio.h>
#include <stdbool.h>

/* Input Keys */
typedef enum {
    InputKeyUp,
    InputKeyDown,
    InputKeyRight,
    InputKeyLeft,
    InputKeyOk,
    InputKeyBack,
    InputKeyMAX, /**< Special value */
} InputKey;

/* Light */
typedef enum {
    LightRed = (1 << 0),
    LightGreen = (1 << 1),
    LightBlue = (1 << 2),
    LightBacklight = (1 << 3),
} Light;

extern const GpioPin gpio_display_rst_n;
extern const GpioPin gpio_display_di;
