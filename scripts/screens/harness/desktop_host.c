/*
 * Desktop-layer rendering: the real gui.c compositor (desktop layer + status
 * bar) and the real power service battery icon callback, compiled into this
 * unit so their static functions can be called directly.
 */
#include <gui/gui.c>
#include <power/power_service/power.c>

#include "screen.h"

/* storage.c storage_app_sd_icon_draw_callback(), StorageStatusOK branch */
static void sd_icon_draw(Canvas* canvas, void* context) {
    (void)context;
    canvas_draw_icon(canvas, 0, 0, &I_SDcardMounted_11x8);
}

void screen_draw_desktop(Canvas* canvas, ViewPortDrawCallback draw, void* context) {
    static Gui gui;
    memset(&gui, 0, sizeof(gui));
    for(size_t i = 0; i < GuiLayerMAX; i++) ViewPortArray_init(gui.layers[i]);
    gui.canvas = canvas;

    /* storage service: SD card icon (storage_app_alloc) */
    ViewPort* sd = view_port_alloc();
    view_port_set_width(sd, icon_get_width(&I_SDcardMounted_11x8));
    view_port_draw_callback_set(sd, sd_icon_draw, NULL);
    gui_add_view_port(&gui, sd, GuiLayerStatusBarLeft);

    /* power service: battery, default settings (bar style), 100 %, not charging */
    static Power power;
    memset(&power, 0, sizeof(power));
    power.info.gauge_is_ok = true;
    power.info.charge = 100;
    power.info.voltage_battery_charge_limit = 4.208f; /* BQ25896 default VREG */
    power.state = PowerStateNotCharging;
    power.displayBatteryPercentage = 0; /* DISPLAY_BATTERY_BAR */
    ViewPort* battery = power_battery_view_port_alloc(&power);
    gui_add_view_port(&gui, battery, GuiLayerStatusBarRight);

    /* desktop view dispatcher (ViewDispatcherTypeDesktop -> GuiLayerDesktop) */
    ViewPort* desktop = view_port_alloc();
    view_port_draw_callback_set(desktop, draw, context);
    gui_add_view_port(&gui, desktop, GuiLayerDesktop);

    /* gui_redraw(), not locked, no fullscreen/window view port */
    gui_redraw_desktop(&gui);
    gui_redraw_status_bar(&gui, false);
}

void screen_draw_fullscreen(Canvas* canvas, ViewPortDrawCallback draw, void* context) {
    static Gui gui;
    memset(&gui, 0, sizeof(gui));
    for(size_t i = 0; i < GuiLayerMAX; i++) ViewPortArray_init(gui.layers[i]);
    gui.canvas = canvas;

    ViewPort* fs = view_port_alloc();
    view_port_draw_callback_set(fs, draw, context);
    gui_add_view_port(&gui, fs, GuiLayerFullscreen);

    /* gui_redraw(): a fullscreen view port covers the status bar */
    gui_redraw_fs(&gui);
}

static void screen_desktop_view_draw(Canvas* canvas, void* context) {
    /* view_dispatcher_draw_callback() */
    view_draw(context, canvas);
}

void screen_draw_desktop_view(Canvas* canvas, View* view) {
    screen_draw_desktop(canvas, screen_desktop_view_draw, view);
}
