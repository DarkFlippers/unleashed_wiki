/* iButton screens: applications/main/ibutton */
#include "screen.h"
#include "spec_util.h"

#define SCENES "applications/main/ibutton/scenes/"

/* Placeholder key: Dallas DS1990, ROM 01 A2 3B 1C 0E 00 00 25 (valid CRC8),
 * saved as "Front_door" */
static const uint8_t demo_rom[] = {0x01, 0xA2, 0x3B, 0x1C, 0x0E, 0x00, 0x00, 0x25};
#define DEMO_FILE "Front_door"

static void noop_widget_cb(GuiButtonType result, InputType type, void* context) {
    (void)result;
    (void)type;
    (void)context;
}

SCREEN(ibutton_menu,
       .file = "ibutton/menu",
       .section = "ibutton",
       .title = "iButton main menu",
       .menu_path = "iButton",
       .scene = SCENES "ibutton_scene_start.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(submenu, "Read", "Saved", "Add Manually", "Settings", NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(ibutton_read,
       .file = "ibutton/read",
       .section = "ibutton",
       .title = "Waiting for a key",
       .menu_path = "iButton → Read",
       .scene = SCENES "ibutton_scene_read.c") {
    Popup* popup = popup_alloc();
    popup_set_header(popup, "Reading", 95, 26, AlignCenter, AlignBottom);
    popup_set_text(popup, "Connect key\nwith pogo pins", 95, 30, AlignCenter, AlignTop);
    popup_set_icon(popup, 0, 10, &I_DolphinWait_59x54);
    screen_draw_view(canvas, popup_get_view(popup));
}

SCREEN(ibutton_read_success,
       .file = "ibutton/read_success",
       .section = "ibutton",
       .title = "Read result: Dallas DS1990",
       .menu_path = "iButton → Read → (key read)",
       .scene = SCENES "ibutton_scene_read_success.c") {
    Widget* widget = widget_alloc();
    widget_add_button_element(widget, GuiButtonTypeLeft, "Retry", noop_widget_cb, NULL);
    widget_add_button_element(widget, GuiButtonTypeRight, "More", noop_widget_cb, NULL);
    widget_add_string_element(widget, 0, 2, AlignLeft, AlignTop, FontPrimary, "Dallas DS1990");
    /* dallas_ds1990_render_brief_data() */
    FuriString* s = furi_string_alloc_set("ID: ");
    for(size_t i = 0; i < sizeof(demo_rom); i++) furi_string_cat_printf(s, "%02X ", demo_rom[i]);
    furi_string_cat_printf(s, "\nFamily Code: %02X\n", demo_rom[0]);
    widget_add_string_multiline_element(
        widget, 0, 16, AlignLeft, AlignTop, FontSecondary, furi_string_get_cstr(s));
    screen_draw_view(canvas, widget_get_view(widget));
}

SCREEN(ibutton_saved_menu,
       .file = "ibutton/saved_menu",
       .section = "ibutton",
       .title = "Saved key menu",
       .menu_path = "iButton → Saved → (file)",
       .scene = SCENES "ibutton_scene_saved_key_menu.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(submenu, "Emulate", "Write ID", "Edit", "Rename", "Delete", "Info", NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(ibutton_emulate,
       .file = "ibutton/emulate",
       .section = "ibutton",
       .title = "Emulating a saved key",
       .menu_path = "iButton → Saved → (file) → Emulate",
       .scene = SCENES "ibutton_scene_emulate.c") {
    Widget* widget = widget_alloc();
    widget_add_icon_element(widget, 3, 10, &I_iButtonKey_49x44);
    widget_add_text_box_element(
        widget, 52, 24, 75, 40, AlignCenter, AlignTop, "[DS1990]\n" DEMO_FILE, true);
    widget_add_string_multiline_element(
        widget, 88, 10, AlignCenter, AlignTop, FontPrimary, "Emulating");
    screen_draw_view(canvas, widget_get_view(widget));
}

SCREEN(ibutton_write,
       .file = "ibutton/write",
       .section = "ibutton",
       .title = "Writing a blank",
       .menu_path = "iButton → Saved → (file) → Write ID",
       .scene = SCENES "ibutton_scene_write.c") {
    Widget* widget = widget_alloc();
    widget_add_icon_element(widget, 3, 10, &I_iButtonKey_49x44);
    widget_add_text_box_element(
        widget, 52, 24, 75, 40, AlignCenter, AlignTop, "[DS1990]\n" DEMO_FILE "\n(RW1990.1)", true);
    widget_add_string_multiline_element(
        widget, 88, 5, AlignCenter, AlignTop, FontPrimary, "Writing ID");
    screen_draw_view(canvas, widget_get_view(widget));
}

SCREEN(ibutton_add_type,
       .file = "ibutton/add_manually",
       .section = "ibutton",
       .title = "Add Manually: key type",
       .menu_path = "iButton → Add Manually",
       .scene = SCENES "ibutton_scene_add_type.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu,
        "Dallas DS1990",
        "Dallas DS1992",
        "Dallas DS1996",
        "Dallas DS1971",
        "Dallas DS1420",
        "Dallas (non-specific)",
        "Cyfral",
        "Metakom",
        NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}
