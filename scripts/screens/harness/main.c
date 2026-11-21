/*
 * flipper_screens: renders every registered ScreenSpec with the real
 * firmware Canvas/u8g2 code and writes qFlipper-identical PNGs.
 *
 * qFlipper (application/screencanvas.cpp + components/StreamOverlay.qml):
 *   foreground  = "black"                      -> #000000
 *   background  = Theme.color.lightorange2     -> #FE8A2C
 *   saveImage(url, 4)                          -> 128x64 scaled x4 = 512x256,
 *                                                 nearest neighbour, RGB
 * Pixel decode: byte (y/8)*128 + x, bit (y%8)  (u8g2 vertical_top_lsb buffer).
 */
#include "screen.h"
#include "png.h"

#include <gui/canvas_i.h>
#include <gui/view_i.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_SCREENS 512

static const ScreenSpec* specs[MAX_SCREENS];
static size_t specs_count = 0;

void screen_register(const ScreenSpec* spec) {
    if(specs_count < MAX_SCREENS) specs[specs_count++] = spec;
}

void screen_draw_view(Canvas* canvas, View* view) {
    /* gui_redraw(): canvas_reset() then gui_redraw_fs() frame; the view
     * dispatcher copies the view orientation to its ViewPort, and
     * view_port_draw() applies it to the canvas */
    static const CanvasOrientation map[] = {
        [ViewOrientationHorizontal] = CanvasOrientationHorizontal,
        [ViewOrientationHorizontalFlip] = CanvasOrientationHorizontalFlip,
        [ViewOrientationVertical] = CanvasOrientationVertical,
        [ViewOrientationVerticalFlip] = CanvasOrientationVerticalFlip,
    };
    canvas_set_orientation(canvas, CanvasOrientationHorizontal);
    canvas_frame_set(canvas, 0, 0, 128, 64);
    canvas_set_orientation(canvas, map[view->orientation]);
    view_draw(view, canvas);
}

static int mkdir_p(const char* path) {
    char tmp[1024];
    snprintf(tmp, sizeof(tmp), "%s", path);
    for(char* p = tmp + 1; *p; p++) {
        if(*p == '/') {
            *p = 0;
            if(mkdir(tmp, 0755) && errno != EEXIST) return -1;
            *p = '/';
        }
    }
    if(mkdir(tmp, 0755) && errno != EEXIST) return -1;
    return 0;
}

static void json_str(FILE* f, const char* s) {
    fputc('"', f);
    for(; s && *s; s++) {
        if(*s == '"' || *s == '\\')
            fprintf(f, "\\%c", *s);
        else if(*s == '\n')
            fputs("\\n", f);
        else
            fputc(*s, f);
    }
    fputc('"', f);
}

static const char* section_order[] = {
    "desktop", "mainmenu", "subghz", "lfrfid", "nfc", "infrared", "gpio",
    "ibutton", "badusb", "apps", "settings", NULL};

static int section_rank(const char* s) {
    for(int i = 0; section_order[i]; i++)
        if(!strcmp(section_order[i], s)) return i;
    return 100;
}

static int spec_cmp(const void* a, const void* b) {
    const ScreenSpec* x = *(const ScreenSpec* const*)a;
    const ScreenSpec* y = *(const ScreenSpec* const*)b;
    int r = section_rank(x->section) - section_rank(y->section);
    if(r) return r;
    return (x < y) ? -1 : (x > y); /* stable-ish: definition order within a file */
}

int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stderr, "usage: %s <out_dir> [--only <substr>] [--raw <file.bin>]\n", argv[0]);
        return 2;
    }
    const char* out_dir = argv[1];
    const char* only = NULL;
    for(int i = 2; i < argc; i++) {
        if(!strcmp(argv[i], "--only") && i + 1 < argc) only = argv[++i];
    }

    qsort(specs, specs_count, sizeof(specs[0]), spec_cmp);

    Canvas* canvas = canvas_init();
    char path[1024];
    snprintf(path, sizeof(path), "%s/manifest.json", out_dir);
    FILE* manifest = only ? NULL : fopen(path, "w");
    if(manifest) fputs("[\n", manifest);

    size_t written = 0;
    for(size_t i = 0; i < specs_count; i++) {
        const ScreenSpec* s = specs[i];
        if(only && !strstr(s->file, only)) continue;

        /* gui_redraw() */
        canvas_reset(canvas);
        s->render(canvas);

        uint8_t* fb = canvas_get_buffer(canvas);
        snprintf(path, sizeof(path), "%s/%s.png", out_dir, s->file);
        char dir[1024];
        snprintf(dir, sizeof(dir), "%s", path);
        *strrchr(dir, '/') = 0;
        mkdir_p(dir);
        /* rpc_gui orientation -> qFlipper GuiScreenFrameResponse::screenOrientation()
         * -> ScreenCanvas::canvasTransform() */
        int rotation = 0;
        switch(canvas->orientation) {
        case CanvasOrientationHorizontalFlip: rotation = 180; break;
        case CanvasOrientationVertical: rotation = 90; break;
        case CanvasOrientationVerticalFlip: rotation = -90; break;
        default: break;
        }
        canvas_set_orientation(canvas, CanvasOrientationHorizontal);
        if(png_write_qflipper(path, fb, rotation)) {
            fprintf(stderr, "failed to write %s\n", path);
            return 1;
        }
        /* raw 1bpp frame (1024 bytes, exactly what RPC/qFlipper receives) */
        if(getenv("SCREENS_RAW")) {
            snprintf(path, sizeof(path), "%s/%s.bin", out_dir, s->file);
            FILE* rf = fopen(path, "wb");
            fwrite(fb, 1, 1024, rf);
            fclose(rf);
        }

        if(manifest) {
            fprintf(manifest, "%s  {\"file\": ", written ? ",\n" : "");
            char url[512];
            snprintf(url, sizeof(url), "/screens/%s.png", s->file);
            json_str(manifest, url);
            fputs(", \"section\": ", manifest);
            json_str(manifest, s->section);
            fputs(", \"title\": ", manifest);
            json_str(manifest, s->title);
            fputs(", \"menuPath\": ", manifest);
            json_str(manifest, s->menu_path);
            fputs(", \"scene\": ", manifest);
            json_str(manifest, s->scene);
            fputs("}", manifest);
        }
        written++;
        printf("  %s.png\n", s->file);
    }
    if(manifest) {
        fputs("\n]\n", manifest);
        fclose(manifest);
    }
    printf("%zu screens rendered\n", written);
    return 0;
}
