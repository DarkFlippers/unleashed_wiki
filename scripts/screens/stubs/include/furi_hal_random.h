#pragma once
#include <stdint.h>
#include <stddef.h>
/* deterministic "random" for reproducible screenshots */
static inline uint32_t furi_hal_random_get(void) {
    return 0;
}
static inline void furi_hal_random_fill_buf(uint8_t* buf, uint32_t len) {
    for(uint32_t i = 0; i < len; i++) buf[i] = 0;
}
