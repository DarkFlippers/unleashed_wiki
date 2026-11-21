/* Bad USB screens: applications/main/bad_usb */
#include "screen.h"
#include "spec_util.h"

#include <bad_usb/views/bad_usb_view.h>
#include <bad_usb/helpers/ducky_script.h>

#define SCENES "applications/main/bad_usb/scenes/"

/* Placeholder script: demo_windows.txt, 34 lines, US layout */
static BadUsb* demo_view(BadUsbWorkerState state, size_t line_cur, uint32_t elapsed) {
    BadUsb* v = bad_usb_view_alloc();
    bad_usb_view_set_file_name(v, "demo_windows");
    bad_usb_view_set_layout(v, "en-US");
    bad_usb_view_set_interface(v, BadUsbHidInterfaceUsb);
    BadUsbState st = {.state = state, .line_cur = line_cur, .line_nb = 34, .elapsed = elapsed};
    bad_usb_view_set_state(v, &st);
    return v;
}

SCREEN(badusb_idle,
       .file = "badusb/script_ready",
       .section = "badusb",
       .title = "Script loaded, ready to run",
       .menu_path = "Bad USB → (script)",
       .scene = SCENES "bad_usb_scene_work.c") {
    screen_draw_view(canvas, bad_usb_view_get_view(demo_view(BadUsbStateIdle, 0, 0)));
}

SCREEN(badusb_running,
       .file = "badusb/script_running",
       .section = "badusb",
       .title = "Script running",
       .menu_path = "Bad USB → (script) → Run",
       .scene = SCENES "bad_usb_scene_work.c") {
    screen_draw_view(canvas, bad_usb_view_get_view(demo_view(BadUsbStateRunning, 12, 3417)));
}

SCREEN(badusb_not_connected,
       .file = "badusb/not_connected",
       .section = "badusb",
       .title = "Waiting for a USB host",
       .menu_path = "Bad USB → (script)",
       .scene = SCENES "bad_usb_scene_work.c") {
    screen_draw_view(canvas, bad_usb_view_get_view(demo_view(BadUsbStateNotConnected, 0, 0)));
}

SCREEN(badusb_config,
       .file = "badusb/config",
       .section = "badusb",
       .title = "Bad USB settings (USB)",
       .menu_path = "Bad USB → (script) → Config",
       .scene = SCENES "bad_usb_scene_config.c") {
    VariableItemList* list = variable_item_list_alloc();
    variable_item_list_add(list, "Keyboard Layout (global)", 0, NULL, NULL);
    spec_var_item(list, "Connection", 2, 0, "USB");
    variable_item_list_add(list, "Set Manufacturer Name", 0, NULL, NULL);
    variable_item_list_add(list, "Set Product Name", 0, NULL, NULL);
    variable_item_list_add(list, "Set VID and PID", 0, NULL, NULL);
    variable_item_list_add(list, "Randomize VID and PID", 0, NULL, NULL);
    variable_item_list_add(list, "Restore USB Defaults", 0, NULL, NULL);
    screen_draw_view(canvas, variable_item_list_get_view(list));
}
