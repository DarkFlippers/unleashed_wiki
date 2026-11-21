#include "png.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <stdbool.h>

static void be32(uint8_t* p, uint32_t v) {
    p[0] = v >> 24;
    p[1] = v >> 16;
    p[2] = v >> 8;
    p[3] = v;
}

static void chunk(FILE* f, const char* type, const uint8_t* data, uint32_t len) {
    uint8_t hdr[8];
    be32(hdr, len);
    memcpy(hdr + 4, type, 4);
    fwrite(hdr, 1, 8, f);
    if(len) fwrite(data, 1, len, f);
    uLong crc = crc32(0, (const Bytef*)type, 4);
    if(len) crc = crc32(crc, data, len);
    uint8_t c[4];
    be32(c, (uint32_t)crc);
    fwrite(c, 1, 4, f);
}

static int fb_pixel(const uint8_t* fb, int x, int y) {
    return fb[(y / 8) * 128 + x] & (1 << (y % 8));
}

int png_write_qflipper(const char* path, const uint8_t* fb, int rotation) {
    const bool portrait = rotation == 90 || rotation == -90;
    const int s = QFLIPPER_SCALE, w = (portrait ? 64 : 128) * s, h = (portrait ? 128 : 64) * s;
    const size_t stride = 1 + (size_t)w * 3;
    uint8_t* raw = malloc(stride * h);
    for(int y = 0; y < h; y++) {
        uint8_t* row = raw + (size_t)y * stride;
        row[0] = 0; /* filter: none */
        for(int x = 0; x < w; x++) {
            /* ScreenCanvas::canvas(): scaled() then transformed(rotate(rotation)) */
            int X = x / s, Y = y / s, on;
            if(rotation == 90)
                on = fb_pixel(fb, Y, 63 - X);
            else if(rotation == -90)
                on = fb_pixel(fb, 127 - Y, X);
            else if(rotation == 180)
                on = fb_pixel(fb, 127 - X, 63 - Y);
            else
                on = fb_pixel(fb, X, Y);
            uint8_t* p = row + 1 + x * 3;
            p[0] = on ? QFLIPPER_FG_R : QFLIPPER_BG_R;
            p[1] = on ? QFLIPPER_FG_G : QFLIPPER_BG_G;
            p[2] = on ? QFLIPPER_FG_B : QFLIPPER_BG_B;
        }
    }
    uLongf zlen = compressBound(stride * h);
    uint8_t* z = malloc(zlen);
    compress2(z, &zlen, raw, stride * h, 9);

    FILE* f = fopen(path, "wb");
    if(!f) {
        free(raw);
        free(z);
        return -1;
    }
    static const uint8_t sig[8] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n'};
    fwrite(sig, 1, 8, f);
    uint8_t ihdr[13];
    be32(ihdr, w);
    be32(ihdr + 4, h);
    ihdr[8] = 8; /* bit depth */
    ihdr[9] = 2; /* colour type: truecolour RGB (QImage::Format_RGB32 is saved as RGB) */
    ihdr[10] = 0;
    ihdr[11] = 0;
    ihdr[12] = 0;
    chunk(f, "IHDR", ihdr, 13);
    chunk(f, "IDAT", z, (uint32_t)zlen);
    chunk(f, "IEND", NULL, 0);
    fclose(f);
    free(raw);
    free(z);
    return 0;
}
