#pragma once
#include <stdint.h>

#define QFLIPPER_SCALE 4
#define QFLIPPER_FG_R  0x00
#define QFLIPPER_FG_G  0x00
#define QFLIPPER_FG_B  0x00
#define QFLIPPER_BG_R  0xFE
#define QFLIPPER_BG_G  0x8A
#define QFLIPPER_BG_B  0x2C

/* Write a 128x64 u8g2 framebuffer as a qFlipper-style screenshot PNG.
 * rotation is qFlipper's canvasTransform() for the frame orientation:
 * 0 landscape, 180 inverted landscape, 90 portrait, -90 inverted portrait. */
int png_write_qflipper(const char* path, const uint8_t* fb, int rotation);
