/* Sub-GHz screens: applications/main/subghz */
#include "screen.h"
#include "spec_util.h"

#include <subghz/views/receiver.h>
#include <subghz/views/subghz_read_raw.h>
#include <subghz/views/transmitter.h>
#include <lib/subghz/types.h>

/* The frequency analyzer keeps its model private, so the firmware file is
 * compiled into this unit to fill the model like the worker callback does. */
#include <subghz/plugins/frequency_analyzer/subghz_frequency_analyzer.c>

#define SCENES "applications/main/subghz/scenes/"

/* Placeholder signal: Princeton 24 bit, key 0x5D2F14, 433.92 MHz AM650 */
#define DEMO_KEY  0x5D2F14u
#define DEMO_BITS 24
#define DEMO_FREQ "433.92"

/* subghz_protocol_blocks_reverse_key() */
static uint32_t reverse_key(uint64_t key, uint8_t bits) {
    uint64_t r = 0;
    for(uint8_t i = 0; i < bits; i++) r = (r << 1) | ((key >> i) & 1);
    return (uint32_t)r;
}

/* subghz_protocol_decoder_princeton_get_string() with btn 4 (4b) */
static void princeton_string(FuriString* out) {
    furi_string_printf(
        out,
        "%s %dbit\r\n"
        "Key:0x%08lX\r\n"
        "Yek:0x%08lX\r\n"
        "Sn:0x%05lX Btn:%01X (4b)\r\n"
        "Te:%luus  GT:Te*%lu\r\n",
        "Princeton",
        DEMO_BITS,
        (unsigned long)(DEMO_KEY & 0xFFFFFF),
        (unsigned long)reverse_key(DEMO_KEY, DEMO_BITS),
        (unsigned long)(DEMO_KEY >> 4),
        (unsigned)(DEMO_KEY & 0xF),
        (unsigned long)403,
        (unsigned long)30);
}

SCREEN(subghz_menu,
       .file = "subghz/menu",
       .section = "subghz",
       .title = "Sub-GHz main menu",
       .menu_path = "Sub-GHz",
       .scene = SCENES "subghz_scene_start.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu,
        "Read",
        "Read RAW",
        "Saved",
        "Add Manually",
        "Add Manually [Advanced]",
        "Frequency Analyzer",
        "Radio Settings",
        NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

/* subghz_scene_receiver_update_statusbar(), history empty */
SCREEN(subghz_read_scanning,
       .file = "subghz/read",
       .section = "subghz",
       .title = "Read: waiting for a signal",
       .menu_path = "Sub-GHz → Read",
       .scene = SCENES "subghz_scene_receiver.c") {
    SubGhzViewReceiver* r = subghz_view_receiver_alloc();
    subghz_view_receiver_set_mode(r, SubGhzViewReceiverModeLive);
    subghz_view_receiver_add_data_statusbar(
        r, DEMO_FREQ, "Int        Mod: AM650", "00", false, false, false);
    subghz_view_receiver_set_radio_device_type(r, SubGhzRadioDeviceTypeInternal);
    subghz_receiver_rssi(r, -78.0f);
    screen_draw_view(canvas, subghz_view_receiver_get_view(r));
}

SCREEN(subghz_read_list,
       .file = "subghz/read_list",
       .section = "subghz",
       .title = "Read: received signals",
       .menu_path = "Sub-GHz → Read",
       .scene = SCENES "subghz_scene_receiver.c") {
    SubGhzViewReceiver* r = subghz_view_receiver_alloc();
    subghz_view_receiver_set_mode(r, SubGhzViewReceiverModeLive);
    subghz_view_receiver_add_item_to_menu(r, "Princeton 5D2F14", "12:31:07 ", SubGhzProtocolTypeStatic);
    subghz_view_receiver_add_item_to_menu(r, "CAME 12bit", "12:32:40 ", SubGhzProtocolTypeStatic);
    subghz_view_receiver_add_item_to_menu(r, "KL: DoorHan", "12:33:15 ", SubGhzProtocolTypeDynamic);
    subghz_view_receiver_add_data_statusbar(r, DEMO_FREQ, "AM65", "03", false, false, false);
    subghz_view_receiver_set_radio_device_type(r, SubGhzRadioDeviceTypeInternal);
    subghz_view_receiver_set_idx_menu(r, 0);
    subghz_receiver_rssi(r, -71.0f);
    screen_fire_oneshot_timers(); /* the "time received" hint has flipped back */
    screen_draw_view(canvas, subghz_view_receiver_get_view(r));
}

SCREEN(subghz_receiver_info,
       .file = "subghz/signal_info",
       .section = "subghz",
       .title = "Received signal info",
       .menu_path = "Sub-GHz → Read → (signal)",
       .scene = SCENES "subghz_scene_receiver_info.c") {
    Widget* w = widget_alloc();
    FuriString* text = furi_string_alloc();
    princeton_string(text);
    widget_add_string_element(w, 78, 0, AlignLeft, AlignTop, FontSecondary, DEMO_FREQ);
    widget_add_string_element(w, 113, 0, AlignLeft, AlignTop, FontSecondary, "AM");
    widget_add_string_multiline_element(
        w, 0, 0, AlignLeft, AlignTop, FontSecondary, furi_string_get_cstr(text));
    widget_add_button_element(w, GuiButtonTypeRight, "Save", NULL, NULL);
    widget_add_button_element(w, GuiButtonTypeCenter, "Send", NULL, NULL);
    screen_draw_view(canvas, widget_get_view(w));
}

SCREEN(subghz_receiver_config,
       .file = "subghz/read_config",
       .section = "subghz",
       .title = "Read: Config",
       .menu_path = "Sub-GHz → Read → Config",
       .scene = SCENES "subghz_scene_receiver_config.c") {
    VariableItemList* l = variable_item_list_alloc();
    spec_var_item(l, "Frequency", 60, 44, DEMO_FREQ);
    spec_var_item(l, "Modulation", 5, 1, "AM650");
    spec_var_item(l, "Hopping", 12, 0, "OFF");
    spec_var_item(l, "Bin RAW", 2, 0, "OFF");
    spec_var_item(l, "Ignore ReversRB2", 2, 0, "OFF");
    spec_var_item(l, "Ignore Alarms", 2, 0, "OFF");
    spec_var_item(l, "Ignore Sensors", 2, 0, "OFF");
    spec_var_item(l, "Ignore Princeton", 2, 0, "OFF");
    spec_var_item(l, "Ignore Nice Flor-S / Nice One", 2, 0, "OFF");
    spec_var_item(l, "Delete old signals when memory is full", 2, 0, "OFF");
    spec_var_item(l, "Sound", 2, 0, "OFF");
    variable_item_list_add(l, "Reset to default", 1, NULL, NULL);
    variable_item_list_add(l, "Lock Keyboard", 1, NULL, NULL);
    screen_draw_view(canvas, variable_item_list_get_view(l));
}

static void read_raw_noop_cb(SubGhzCustomEvent event, void* context) {
    (void)event;
    (void)context;
}

static SubGhzReadRAW* read_raw_alloc_demo(SubGhzReadRAWStatus status, const char* file) {
    SubGhzReadRAW* rr = subghz_read_raw_alloc(false);
    subghz_read_raw_add_data_statusbar(rr, DEMO_FREQ, "AM650");
    subghz_read_raw_set_radio_device_type(rr, SubGhzRadioDeviceTypeInternal);
    subghz_read_raw_set_status(rr, status, file, -90.0f);
    return rr;
}

SCREEN(subghz_read_raw_idle,
       .file = "subghz/read_raw",
       .section = "subghz",
       .title = "Read RAW: ready to record",
       .menu_path = "Sub-GHz → Read RAW",
       .scene = SCENES "subghz_scene_read_raw.c") {
    SubGhzReadRAW* rr = read_raw_alloc_demo(SubGhzReadRAWStatusStart, "");
    screen_draw_view(canvas, subghz_read_raw_get_view(rr));
}

SCREEN(subghz_read_raw_rec,
       .file = "subghz/read_raw_recording",
       .section = "subghz",
       .title = "Read RAW: recording",
       .menu_path = "Sub-GHz → Read RAW → REC",
       .scene = SCENES "subghz_scene_read_raw.c") {
    SubGhzReadRAW* rr = read_raw_alloc_demo(SubGhzReadRAWStatusStart, "");
    /* the scene has no setter for REC: press OK like the user does */
    subghz_read_raw_set_callback(rr, read_raw_noop_cb, NULL);
    InputEvent ok = {.key = InputKeyOk, .type = InputTypeShort};
    view_input(subghz_read_raw_get_view(rr), &ok);
    /* deterministic RSSI trace: noise floor with two bursts */
    uint32_t seed = 0x1234567;
    for(int i = 0; i < 100; i++) {
        seed = seed * 1103515245u + 12345u;
        float noise = (float)((seed >> 16) % 6);
        bool burst = (i > 28 && i < 46) || (i > 70 && i < 84);
        float rssi = burst ? -45.0f - noise * 2.0f : -86.0f + noise;
        subghz_read_raw_add_data_rssi(rr, rssi, true);
    }
    subghz_read_raw_update_sample_write(rr, 61542);
    screen_draw_view(canvas, subghz_read_raw_get_view(rr));
}

SCREEN(subghz_freq_analyzer,
       .file = "subghz/frequency_analyzer",
       .section = "subghz",
       .title = "Frequency Analyzer",
       .menu_path = "Sub-GHz → Frequency Analyzer",
       .scene = "applications/main/subghz/plugins/frequency_analyzer/subghz_frequency_analyzer.c") {
    SubGhzFrequencyAnalyzer* fa = subghz_frequency_analyzer_alloc(NULL);
    with_view_model(
        fa->view,
        SubGhzFrequencyAnalyzerModel * model,
        {
            memset(model, 0, sizeof(*model));
            model->frequency = 433920000;
            model->frequency_last = 433920000;
            model->rssi = -52.0f;
            model->rssi_last = -48.0f;
            model->signal = true;
            model->trigger = -65.0f;
            model->feedback_level = SubGHzFrequencyAnalyzerFeedbackLevelAll;
            model->history_frequency[0] = 433920000;
            model->history_frequency_rx_count[0] = 3;
            model->history_frequency[1] = 315000000;
            model->history_frequency_rx_count[1] = 1;
        },
        false);
    screen_draw_view(canvas, subghz_frequency_analyzer_get_view(fa));
}

/* first rows of submenu_names[] in plugins/add_manually/subghz_scene_set_type.c */
SCREEN(subghz_add_manually,
       .file = "subghz/add_manually",
       .section = "subghz",
       .title = "Add Manually: protocol list",
       .menu_path = "Sub-GHz → Add Manually",
       .scene = "applications/main/subghz/plugins/add_manually/subghz_scene_set_type.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu,
        "KL: Allmatic",
        "Alutech AT4N",
        "AN-Motors AT4",
        "KL: Aprimatic",
        "KL: ATA PTX4",
        NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(subghz_radio_settings,
       .file = "subghz/radio_settings",
       .section = "subghz",
       .title = "Radio Settings",
       .menu_path = "Sub-GHz → Radio Settings",
       .scene = "applications/main/subghz/plugins/radio_settings/subghz_scene_radio_settings.c") {
    VariableItemList* l = variable_item_list_alloc();
    spec_var_item(l, "Module", 2, 0, "Internal");
    spec_var_item(l, "TX Power", 9, 0, "Preset");
    spec_var_item(l, "Protocol Names", 2, 0, "OFF");
    spec_var_item(l, "Counter Incr.", 17, 0, "+1");
    screen_draw_view(canvas, variable_item_list_get_view(l));
}

SCREEN(subghz_saved_menu,
       .file = "subghz/saved_menu",
       .section = "subghz",
       .title = "Saved signal: actions",
       .menu_path = "Sub-GHz → Saved → (file)",
       .scene = SCENES "subghz_scene_saved_menu.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(submenu, "Emulate", "Rename", "Delete", "Signal Settings", NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(subghz_transmitter,
       .file = "subghz/emulate",
       .section = "subghz",
       .title = "Saved signal: Emulate",
       .menu_path = "Sub-GHz → Saved → (file) → Emulate",
       .scene = SCENES "subghz_scene_transmitter.c") {
    SubGhzViewTransmitter* t = subghz_view_transmitter_alloc();
    FuriString* text = furi_string_alloc();
    princeton_string(text);
    subghz_view_transmitter_set_radio_device_type(t, SubGhzRadioDeviceTypeInternal);
    subghz_view_transmitter_add_data_to_show(t, furi_string_get_cstr(text), DEMO_FREQ, "AM", true);
    screen_draw_view(canvas, subghz_view_transmitter_get_view(t));
}

/* The scene itself reads the saved file through Storage and decodes it, so the
 * variable_item_list is built here the way subghz_scene_signal_settings_on_enter()
 * does for a KeeLoq signal: 11 counter modes, a 16 bit counter and a button. */
SCREEN(subghz_signal_settings,
       .file = "subghz/signal_settings",
       .section = "subghz",
       .title = "Signal Settings",
       .menu_path = "Sub-GHz → Saved → (file) → Signal Settings",
       .scene = "applications/main/subghz/plugins/signal_settings/subghz_scene_signal_settings.c") {
    VariableItemList* list = variable_item_list_alloc();
    spec_var_item(list, "Counter Mode", 11, 0, "System"); /* counter_mode_text[0] */
    spec_var_item(list, "Edit Counter", 1, 0, "4C1A"); /* current_cnt, "%X" */
    spec_var_item(list, "Edit Button", 1, 0, "2"); /* current_btn, "%X" */
    screen_draw_view(canvas, variable_item_list_get_view(list));
}
