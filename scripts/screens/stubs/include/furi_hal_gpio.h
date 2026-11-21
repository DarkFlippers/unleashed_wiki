#pragma once
/* host stub: types copied from targets/f7/furi_hal/furi_hal_gpio.h */
#include <stdbool.h>
#include <stdint.h>
typedef struct {
    void* port;
    uint16_t pin;
} GpioPin;

/**
 * Gpio modes
 */
typedef enum {
    GpioModeInput,
    GpioModeOutputPushPull,
    GpioModeOutputOpenDrain,
    GpioModeAltFunctionPushPull,
    GpioModeAltFunctionOpenDrain,
    GpioModeAnalog,
    GpioModeInterruptRise,
    GpioModeInterruptFall,
    GpioModeInterruptRiseFall,
    GpioModeEventRise,
    GpioModeEventFall,
    GpioModeEventRiseFall,
} GpioMode;

/**
 * Gpio pull modes
 */
typedef enum {
    GpioPullNo,
    GpioPullUp,
    GpioPullDown,
} GpioPull;

/**
 * Gpio speed modes
 */
typedef enum {
    GpioSpeedLow,
    GpioSpeedMedium,
    GpioSpeedHigh,
    GpioSpeedVeryHigh,
} GpioSpeed;

static inline void furi_hal_gpio_write(const GpioPin* gpio, bool state) {
    (void)gpio;
    (void)state;
}
static inline bool furi_hal_gpio_read(const GpioPin* gpio) {
    (void)gpio;
    return false;
}
