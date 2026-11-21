#pragma once
/* host stub: subset of furi_hal used by GUI code */
#include <furi.h>
#include <furi_hal_gpio.h>
#include <furi_hal_resources.h>
#include <furi_hal_spi.h>
#include <furi_hal_version.h>
#include <furi_hal_info.h>
#include <furi_hal_rtc.h>
#include <furi_hal_usb.h>
#include <furi_hal_usb_hid.h>
#include <furi_hal_power.h>
#include <furi_hal_random.h>
/* targets/f7/furi_hal/furi_hal.h pulls this in through furi_hal_bt.h; the
 * desktop info screen reads the copro version from it when SRV_BT is set */
#include <ble_glue.h>
