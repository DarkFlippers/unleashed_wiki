#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
typedef struct { int dummy; } FuriHalSpiBusHandle;
extern FuriHalSpiBusHandle furi_hal_spi_bus_handle_display;
static inline void furi_hal_spi_acquire(FuriHalSpiBusHandle* h) { (void)h; }
static inline void furi_hal_spi_release(FuriHalSpiBusHandle* h) { (void)h; }
static inline bool furi_hal_spi_bus_tx(FuriHalSpiBusHandle* h, const uint8_t* b, size_t s, uint32_t t) { (void)h;(void)b;(void)s;(void)t; return true; }
