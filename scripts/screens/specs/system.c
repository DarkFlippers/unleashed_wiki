/* Desktop and main menu: applications/services/desktop, applications/services/loader */
#include "screen.h"
#include "spec_util.h"

#include <gui/modules/menu.h>
#include <assets_dolphin.h>

/* bubble_animation_draw_callback(): passive frame 0 of the idle animation,
 * bottom-aligned (y = canvas height - icon height), no speech bubble */
static void desktop_animation_draw(Canvas* canvas, void* context) {
    const Icon* frame = context;
    canvas_draw_icon(canvas, 0, canvas_height(canvas) - icon_get_height(frame), frame);
}

SCREEN(desktop_idle,
       .file = "desktop/idle",
       .section = "desktop",
       .title = "Desktop (idle animation)",
       .menu_path = "Desktop",
       .scene = "applications/services/desktop/animations/views/bubble_animation_view.c") {
    screen_draw_desktop(canvas, desktop_animation_draw, (void*)&I_Dolphin_L1_Waves_128x50);
}

static void noop_menu_cb(void* context, uint32_t index) {
    (void)context;
    (void)index;
}

/* loader_menu_add_items(): "Apps", FLIPPER_APPS (by application.fam order),
 * FLIPPER_EXTERNAL_APPS, then "Settings" */
static Menu* main_menu(void) {
    static const struct {
        const char* name;
        const Icon* icon;
    } items[] = {
        {"Apps", &A_Plugins_14},
        {"Sub-GHz", &A_Sub1ghz_14},
        {"Sub-GHz Remote", &A_SubGHzRemote_14},
        {"125 kHz RFID", &A_125khz_14},
        {"NFC", &A_NFC_14},
        {"Infrared", &A_Infrared_14},
        {"GPIO", &A_GPIO_14},
        {"iButton", &A_iButton_14},
        {"Bad USB", &A_BadUsb_14},
        {"U2F", &A_U2F_14},
        {"Clock", &A_Clock_14},
        {"Settings", &A_Settings_14},
    };
    Menu* menu = menu_alloc();
    for(size_t i = 0; i < COUNT_OF(items); i++)
        menu_add_item(menu, items[i].name, items[i].icon, i, noop_menu_cb, NULL);
    return menu;
}

SCREEN(mainmenu_top,
       .file = "mainmenu/main",
       .section = "mainmenu",
       .title = "Main menu",
       .menu_path = "Desktop → OK",
       .scene = "applications/services/loader/loader_menu.c") {
    Menu* menu = main_menu();
    screen_draw_view(canvas, menu_get_view(menu));
}

SCREEN(mainmenu_subghz,
       .file = "mainmenu/subghz",
       .section = "mainmenu",
       .title = "Main menu: Sub-GHz selected",
       .menu_path = "Desktop → OK → Sub-GHz",
       .scene = "applications/services/loader/loader_menu.c") {
    Menu* menu = main_menu();
    menu_set_selected_item(menu, 1);
    screen_draw_view(canvas, menu_get_view(menu));
}

/* ---- desktop views (desktop view dispatcher = GuiLayerDesktop, so the
 * status bar is composited on top; that is what STATUS_BAR_Y_SHIFT in
 * desktop_i.h leaves room for) ------------------------------------------ */
#include <furi_hal_rtc.h>
#include <desktop/views/desktop_view_debug.h>
#include <desktop/views/desktop_view_lock_menu.h>
#include <desktop/views/desktop_view_pin_input.h>

/* desktop_view_debug.c, not declared in its header */
void desktop_debug_render(Canvas* canvas, void* model);

SCREEN(desktop_info_screen,
       .file = "desktop/debug",
       .section = "desktop",
       .title = "Device info / debug screen",
       .menu_path = "Desktop → hold ↓",
       .scene = "applications/services/desktop/views/desktop_view_debug.c") {
    /* uptime comes from furi_get_tick(), frozen at 0 for every other screen */
    screen_host_tick = ((1 * 60 + 23) * 60 + 45) * 1000; /* 1h23m45s */
    /* [D:ON]: the state a long press of OK on this screen leaves behind */
    furi_hal_rtc_set_flag(FuriHalRtcFlagDebug);
    DesktopDebugView* debug = desktop_debug_alloc();
    screen_draw_desktop_view(canvas, desktop_debug_get_view(debug));
    furi_hal_rtc_reset_flag(FuriHalRtcFlagDebug);
    screen_host_tick = 0;
}

SCREEN(desktop_lock_menu,
       .file = "desktop/lock_menu",
       .section = "desktop",
       .title = "Lock menu",
       .menu_path = "Desktop → ↑",
       .scene = "applications/services/desktop/scenes/desktop_scene_lock_menu.c") {
    DesktopLockMenuView* lock_menu = desktop_lock_menu_alloc();
    /* desktop_scene_lock_menu_on_enter(): Bluetooth off (as in the status bar
     * of every rendered screen), stealth and dummy mode off, first item */
    desktop_lock_menu_set_bt_mode_state(lock_menu, false);
    desktop_lock_menu_set_stealth_mode_state(lock_menu, false);
    desktop_lock_menu_set_dummy_mode_state(lock_menu, false);
    desktop_lock_menu_set_idx(lock_menu, 0);
    screen_draw_desktop_view(canvas, desktop_lock_menu_get_view(lock_menu));
}

SCREEN(desktop_pin_input,
       .file = "desktop/pin_input",
       .section = "desktop",
       .title = "PIN entry",
       .menu_path = "Desktop → hold ↑ (with a PIN set) → any arrow",
       .scene = "applications/services/desktop/scenes/desktop_scene_pin_input.c") {
    DesktopViewPinInput* pin_input = desktop_view_pin_input_alloc();
    /* desktop_scene_pin_input_on_enter() */
    desktop_view_pin_input_hide_pin(pin_input, true);
    desktop_view_pin_input_set_label_button(pin_input, "OK");
    desktop_view_pin_input_set_label_secondary(pin_input, 44, 25, "Enter PIN:");
    desktop_view_pin_input_set_pin_position(pin_input, 64, 37);
    desktop_view_pin_input_reset_pin(pin_input);
    /* a four-arrow PIN typed in; OK confirms it */
    const DesktopPinCode pin = {
        .data = {InputKeyUp, InputKeyRight, InputKeyDown, InputKeyLeft},
        .length = 4};
    desktop_view_pin_input_set_pin(pin_input, &pin);
    screen_draw_desktop_view(canvas, desktop_view_pin_input_get_view(pin_input));
}
