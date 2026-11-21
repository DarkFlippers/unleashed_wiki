/* 125 kHz RFID screens: applications/main/lfrfid */
#include "screen.h"
#include "spec_util.h"

#include <lfrfid/views/lfrfid_view_read.h>

#define SCENES "applications/main/lfrfid/scenes/"

/* Placeholder tag: EM-Micro EM4100, data 58 00 7B 1C 3E (RF/64), file "Office_badge" */
static const uint8_t demo_data[] = {0x58, 0x00, 0x7B, 0x1C, 0x3E};
#define DEMO_FILE "Office_badge"

static void noop_widget_cb(GuiButtonType result, InputType type, void* context) {
    (void)result;
    (void)type;
    (void)context;
}

/* "Hex: .." + protocol_em4100_render_data() (no Casi-Rusco line: the first two
 * bits are not zero, so lfrfid_casi_format_render() adds nothing) */
static void em4100_text(FuriString* s) {
    furi_string_cat(s, "Hex: ");
    for(size_t i = 0; i < sizeof(demo_data); i++)
        furi_string_cat_printf(s, "%s%02X", i != 0 ? " " : "", demo_data[i]);
    const uint8_t* data = demo_data;
    furi_string_cat_printf(
        s,
        "\nFC: %03u Card: %05hu CL:%hhu\n"
        "DEZ 8: %08lu\n"
        "DEZ 10: %010lu",
        data[2],
        (uint16_t)((data[3] << 8) | (data[4])),
        (uint8_t)64,
        (unsigned long)((data[2] << 16) | (data[3] << 8) | (data[4])),
        (unsigned long)(((uint32_t)data[1] << 24) | (data[2] << 16) | (data[3] << 8) | (data[4])));
}

SCREEN(lfrfid_menu,
       .file = "lfrfid/menu",
       .section = "lfrfid",
       .title = "125 kHz RFID main menu",
       .menu_path = "125 kHz RFID",
       .scene = SCENES "lfrfid_scene_start.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(submenu, "Read", "Saved", "Add Manually", "Extra Actions", "Settings", NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(lfrfid_read,
       .file = "lfrfid/read",
       .section = "lfrfid",
       .title = "Reading (ASK step)",
       .menu_path = "125 kHz RFID → Read",
       .scene = SCENES "lfrfid_scene_read.c") {
    LfRfidReadView* rv = lfrfid_view_read_alloc();
    lfrfid_view_read_set_read_mode(rv, LfRfidReadAsk);
    screen_draw_view(canvas, lfrfid_view_read_get_view(rv));
}

SCREEN(lfrfid_read_success,
       .file = "lfrfid/read_success",
       .section = "lfrfid",
       .title = "Read result: EM4100",
       .menu_path = "125 kHz RFID → Read → (tag read)",
       .scene = SCENES "lfrfid_scene_read_success.c") {
    Widget* widget = widget_alloc();
    widget_add_text_box_element(
        widget, 16, 2, 112, 14, AlignLeft, AlignTop, "\e#EM-Micro EM4100\e#", true);
    FuriString* s = furi_string_alloc();
    em4100_text(s);
    widget_add_text_scroll_element(widget, 0, 16, 128, 35, furi_string_get_cstr(s));
    widget_add_button_element(widget, GuiButtonTypeLeft, "Retry", noop_widget_cb, NULL);
    widget_add_button_element(widget, GuiButtonTypeRight, "More", noop_widget_cb, NULL);
    widget_add_icon_element(widget, 0, 0, &I_RFIDSmallChip_14x14);
    screen_draw_view(canvas, widget_get_view(widget));
}

SCREEN(lfrfid_saved_menu,
       .file = "lfrfid/saved_menu",
       .section = "lfrfid",
       .title = "Saved tag menu",
       .menu_path = "125 kHz RFID → Saved → (file)",
       .scene = SCENES "lfrfid_scene_saved_key_menu.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu,
        "Emulate",
        "Write",
        "Write and set password",
        "Edit",
        "Rename",
        "Delete",
        "Info",
        NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(lfrfid_saved_info,
       .file = "lfrfid/saved_info",
       .section = "lfrfid",
       .title = "Saved tag info",
       .menu_path = "125 kHz RFID → Saved → (file) → Info",
       .scene = SCENES "lfrfid_scene_saved_info.c") {
    Widget* widget = widget_alloc();
    FuriString* s = furi_string_alloc_printf("Name: %s\n", DEMO_FILE);
    furi_string_cat(s, "\e#EM-Micro EM4100\n");
    em4100_text(s);
    widget_add_text_scroll_element(widget, 0, 0, 128, 64, furi_string_get_cstr(s));
    screen_draw_view(canvas, widget_get_view(widget));
}

SCREEN(lfrfid_emulate,
       .file = "lfrfid/emulate",
       .section = "lfrfid",
       .title = "Emulating a saved tag",
       .menu_path = "125 kHz RFID → Saved → (file) → Emulate",
       .scene = SCENES "lfrfid_scene_emulate.c") {
    Widget* widget = widget_alloc();
    widget_add_icon_element(widget, 0, 0, &I_NFC_dolphin_emulation_51x64);
    widget_add_text_box_element(
        widget,
        51,
        6,
        79,
        50,
        AlignCenter,
        AlignTop,
        "\e#Emulating\e#\n[EM4100]\n" DEMO_FILE,
        false);
    screen_draw_view(canvas, widget_get_view(widget));
}

SCREEN(lfrfid_add_manually,
       .file = "lfrfid/add_manually",
       .section = "lfrfid",
       .title = "Add Manually: tag type",
       .menu_path = "125 kHz RFID → Add Manually",
       .scene = SCENES "lfrfid_scene_save_type.c") {
    /* lfrfid_manual_format_get_label() for every protocol in LFRFIDProtocol
     * order, with Casi-Rusco after EM4100/16 and the HID formats after H10301 */
    static const char* const labels[] = {
        "EM-Micro EM4100", "EM-Micro EM4100/32", "EM-Micro EM4100/16", "Casi-Rusco C10106",
        "Electra", "HID H10301", "HID H10304", "HID H10302", "HID S10401", "HID H10306",
        "HID Corp1000-35", "IDTECK Idteck", "Motorola Indala26", "Kantech IoProxXSF", "AWID",
        "FECAVA FDX-A", "ISO FDX-B", "Generic HIDProx", "Generic HIDExt", "Farpointe Pyramid",
        "Viking", "Jablotron", "Paradox", "PAC/Stanley", "Keri", "Gallagher",
        "Honeywell Nexwatch", "Securakey Radio Key", "Guardall GProxII", "Noralsy",
        "Motorola Indala224",
    };
    Submenu* submenu = submenu_alloc();
    for(size_t i = 0; i < COUNT_OF(labels); i++)
        submenu_add_item(submenu, labels[i], i, spec_noop_submenu_cb, NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

static void noop_byte_input_cb(void* context) {
    (void)context;
}

SCREEN(lfrfid_add_data,
       .file = "lfrfid/add_manually_data",
       .section = "lfrfid",
       .title = "Add Manually: enter data",
       .menu_path = "125 kHz RFID → Add Manually → EM-Micro EM4100",
       .scene = SCENES "lfrfid_scene_save_data.c") {
    static uint8_t data[sizeof(demo_data)];
    memcpy(data, demo_data, sizeof(data));
    ByteInput* bi = byte_input_alloc();
    byte_input_set_header_text(bi, "Enter the data in hex");
    byte_input_set_result_callback(bi, noop_byte_input_cb, NULL, NULL, data, sizeof(data));
    screen_draw_view(canvas, byte_input_get_view(bi));
}

SCREEN(lfrfid_write,
       .file = "lfrfid/write",
       .section = "lfrfid",
       .title = "Writing to a blank",
       .menu_path = "125 kHz RFID → Saved → (file) → Write",
       .scene = SCENES "lfrfid_scene_write.c") {
    Popup* popup = popup_alloc();
    popup_set_icon(popup, 0, 8, &I_NFC_manual_60x50);
    popup_set_header(popup, "Writing", 94, 1, AlignCenter, AlignTop);
    popup_set_text(popup, "[EM4100]\n" DEMO_FILE "\n(T5577)", 94, 14, AlignCenter, AlignTop);
    screen_draw_view(canvas, popup_get_view(popup));
}
