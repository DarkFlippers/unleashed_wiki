/* Settings screens: applications/settings */
#include "screen.h"
#include <gui/modules/submenu.h>
#include <power_settings_app/views/battery_info.h>

SCREEN(settings_battery_info,
       .file = "settings/battery_info",
       .section = "settings",
       .title = "Battery Info",
       .menu_path = "Settings → Power → Battery Info",
       .scene = "applications/settings/power_settings_app/views/battery_info.c") {
    BatteryInfo* bi = battery_info_alloc();
    BatteryInfoModel m = {
        .vbus_voltage = 0.0f,
        .gauge_voltage = 4.15f,
        .gauge_current = -0.0185f,
        .gauge_temperature = 29.0f,
        .charge_voltage_limit = 4.2f,
        .charge = 100,
        .health = 100,
    };
    battery_info_set_data(bi, &m);
    screen_draw_view(canvas, battery_info_get_view(bi));
}

#include <gui/modules/variable_item_list.h>
#include "spec_util.h"

SCREEN(settings_menu,
       .file = "settings/menu",
       .section = "settings",
       .title = "Settings menu",
       .menu_path = "Settings",
       .scene = "applications/services/loader/loader_menu.c") {
    /* loader_menu_build_submenu(): EXTSETTINGS apps, then SETTINGS apps,
     * each sorted by their application.fam order */
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu,
        "About",
        "Bluetooth",
        "Clock & Alarm",
        "Desktop",
        "Expansion Modules",
        "Input",
        "LCD and Notifications",
        "Passport",
        "Power",
        "Storage",
        "System",
        NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(settings_power,
       .file = "settings/power",
       .section = "settings",
       .title = "Power settings",
       .menu_path = "Settings → Power",
       .scene = "applications/settings/power_settings_app/scenes/power_settings_scene_start.c") {
    VariableItemList* list = variable_item_list_alloc();
    variable_item_list_add(list, "Battery Info", 1, NULL, NULL);
    variable_item_list_add(list, "Reboot", 1, NULL, NULL);
    variable_item_list_add(list, "Power OFF", 1, NULL, NULL);
    spec_var_item(list, "Auto PowerOff", 8, 0, "OFF");
    spec_var_item(list, "Limit Charge", 6, 0, "OFF");
    screen_draw_view(canvas, variable_item_list_get_view(list));
}

SCREEN(settings_system,
       .file = "settings/system",
       .section = "settings",
       .title = "System settings",
       .menu_path = "Settings → System",
       .scene = "applications/settings/system/system_settings.c") {
    /* system_settings_alloc() with factory defaults */
    VariableItemList* list = variable_item_list_alloc();
    spec_var_item(list, "Hand Orient", 2, 0, "Righty");
    spec_var_item(list, "Units", 2, 0, "Metric");
    spec_var_item(list, "Time Format", 2, 0, "24h");
    spec_var_item(list, "Date Format", 3, 0, "D/M/Y");
    spec_var_item(list, "Log Level", 7, 0, "Default");
    spec_var_item(list, "Log Device", 3, 0, "USART");
    spec_var_item(list, "Log Baud Rate", 8, 4, "230400");
    spec_var_item(list, "Debug", 2, 0, "OFF");
    spec_var_item(list, "Heap Trace", 2, 0, "None");
    spec_var_item(list, "Sleep Method", 2, 0, "Default");
    spec_var_item(list, "File Naming", 2, 0, "Default");
    screen_draw_view(canvas, variable_item_list_get_view(list));
}

/* ---- Passport ---------------------------------------------------------
 * passport.c keeps its render callback private, so the app source is
 * compiled into this spec (as specs/subghz.c does for the frequency
 * analyzer) and drawn on GuiLayerFullscreen, the way passport_app() does. */
#include <dolphin/dolphin.h>
#include <dolphin_passport/passport.c>

SCREEN(settings_passport,
       .file = "settings/passport",
       .section = "settings",
       .title = "Passport",
       .menu_path = "Settings → Passport",
       .scene = "applications/settings/dolphin_passport/passport.c") {
    /* dolphin_stats(): a placeholder dolphin, level 2 with no butthurt
     * (LEVEL2_THRESHOLD..LEVEL3_THRESHOLD = 301..1800 in dolphin_state.c) */
    DolphinStats stats = {
        .icounter = 900,
        .butthurt = 0,
        .timestamp = 0,
        .level = 2,
        .level_up_is_pending = false,
    };
    screen_draw_fullscreen(canvas, render_callback, &stats);
}

/* ---- Power off --------------------------------------------------------- */
#include <gui/modules/dialog_ex.h>

SCREEN(settings_power_off,
       .file = "settings/power_off",
       .section = "settings",
       .title = "Power off confirmation",
       .menu_path = "Settings → Power → Power OFF (or hold BACK on the desktop)",
       .scene = "applications/settings/power_settings_app/scenes/power_settings_scene_power_off.c") {
    /* power_settings_scene_power_off_on_enter(), happy_mode off */
    DialogEx* dialog = dialog_ex_alloc();
    dialog_ex_set_header(dialog, "Turn Off Device?", 64, 0, AlignCenter, AlignTop);
    dialog_ex_set_text(dialog, "   I will be\nwaiting for\n you here...", 78, 14, AlignLeft, AlignTop);
    dialog_ex_set_icon(dialog, 24, 10, &I_dolph_cry_49x54);
    dialog_ex_set_left_button_text(dialog, "Battery");
    dialog_ex_set_right_button_text(dialog, "Power Off");
    screen_draw_view(canvas, dialog_ex_get_view(dialog));
}
