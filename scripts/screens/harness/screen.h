#pragma once
/*
 * Screen spec API.
 *
 * A spec builds a real firmware GUI module (submenu, widget, popup, ...)
 * exactly like the app scene does, then draws it onto the 128x64 canvas.
 * Each spec file registers its screens with SCREEN(...).
 */
#include <gui/view_port.h>
#include <furi.h>
#include <gui/canvas.h>
#include <gui/canvas_i.h>
#include <gui/view.h>
#include <gui/view_i.h>
#include <gui/elements.h>
#include <assets_icons.h>

typedef void (*ScreenRenderFn)(Canvas* canvas);

typedef struct {
    const char* file; /* e.g. "subghz/read" -> <out>/subghz/read.png */
    const char* section;
    const char* title;
    const char* menu_path;
    const char* scene; /* firmware source file the screen comes from */
    ScreenRenderFn render;
} ScreenSpec;

void screen_register(const ScreenSpec* spec);

#define SCREEN(id, ...)                                                 \
    static void id##_render(Canvas* canvas);                            \
    static const ScreenSpec id##_spec = {__VA_ARGS__, .render = id##_render}; \
    __attribute__((constructor)) static void id##_register(void) {      \
        screen_register(&id##_spec);                                    \
    }                                                                   \
    static void id##_render(Canvas* canvas)

/* Draw a fullscreen View the same way ViewDispatcher + GUI do it
 * (draw callback on a 128x64 frame; enter callbacks are not run). */
void screen_draw_view(Canvas* canvas, View* view);

/* Draw the desktop layer (draw callback on the full 128x64 frame) and then
 * the status bar on top, as gui_redraw() does when no fullscreen or window
 * view port is active. Status bar: SD card icon + battery (default settings). */
void screen_draw_desktop(Canvas* canvas, ViewPortDrawCallback draw, void* context);

/* Draw a View that lives in the desktop's own view dispatcher
 * (ViewDispatcherTypeDesktop -> GuiLayerDesktop): the view first, the status
 * bar on top, as gui_redraw() composites them. */
void screen_draw_desktop_view(Canvas* canvas, View* view);

/* Draw a ViewPort that the app added to GuiLayerFullscreen, the way
 * gui_redraw() -> gui_redraw_fs() does it: full 128x64 frame, no status bar
 * (e.g. dolphin_passport/passport.c, applications/system/snake_game). */
void screen_draw_fullscreen(Canvas* canvas, ViewPortDrawCallback draw, void* context);

/* furi_get_tick() value used while drawing (0 unless a spec sets it, see
 * stubs/furi_stubs.c). */
extern uint32_t screen_host_tick;

/* Fire every running one-shot timer once (emulates time passing, e.g. a
 * transient "time of reception" hint flipping back to the signal name). */
void screen_fire_oneshot_timers(void);
