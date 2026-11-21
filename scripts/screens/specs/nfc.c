/* NFC screens: applications/main/nfc */
#include "screen.h"
#include "spec_util.h"

#include <nfc/views/detect_reader.h>
#include <nfc/views/dict_attack.h>

#define SCENES "applications/main/nfc/scenes/"
#define MFC_SCENES "applications/main/nfc/helpers/protocol_support/mf_classic/mf_classic_extra_scenes.c"

/* Placeholder card: MIFARE Classic 1K, UID 04 A2 3B 1C, ATQA 00 04, SAK 08 */
static const uint8_t demo_uid[] = {0x04, 0xA2, 0x3B, 0x1C};

static void noop_widget_cb(GuiButtonType result, InputType type, void* context) {
    (void)result;
    (void)type;
    (void)context;
}

SCREEN(nfc_menu,
       .file = "nfc/menu",
       .section = "nfc",
       .title = "NFC main menu",
       .menu_path = "NFC",
       .scene = SCENES "nfc_scene_start.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu, "Read", "Extract MFC Keys", "Saved", "Extra Actions", "Add Manually", NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(nfc_reading,
       .file = "nfc/reading",
       .section = "nfc",
       .title = "Reading a card",
       .menu_path = "NFC → Read",
       .scene = SCENES "nfc_scene_detect.c") {
    Popup* popup = popup_alloc();
    popup_set_header(popup, "Reading", 97, 15, AlignCenter, AlignTop);
    popup_set_text(popup, "Hold card next\nto Flipper's back", 94, 27, AlignCenter, AlignTop);
    popup_set_icon(popup, 0, 8, &I_NFC_manual_60x50);
    screen_draw_view(canvas, popup_get_view(popup));
}

SCREEN(nfc_dict_attack,
       .file = "nfc/dict_attack",
       .section = "nfc",
       .title = "MIFARE Classic dictionary attack",
       .menu_path = "NFC → Read (MIFARE Classic)",
       .scene = MFC_SCENES) {
    DictAttack* da = dict_attack_alloc();
    dict_attack_set_type(da, DictAttackTypeMfClassic);
    dict_attack_set_header(da, "MF Classic System Dictionary");
    dict_attack_set_card_state(da, true);
    dict_attack_set_sectors_total(da, 16);
    dict_attack_set_sectors_read(da, 9);
    dict_attack_set_keys_found(da, 19);
    dict_attack_set_current_sector(da, 9);
    dict_attack_set_total_dict_keys(da, 2271);
    dict_attack_set_current_dict_key(da, 1244);
    screen_draw_view(canvas, dict_attack_get_view(da));
}

SCREEN(nfc_card_info,
       .file = "nfc/card_info",
       .section = "nfc",
       .title = "Read result: MIFARE Classic 1K",
       .menu_path = "NFC → Read → (card read)",
       .scene = "applications/main/nfc/helpers/protocol_support/mf_classic/mf_classic.c") {
    Widget* widget = widget_alloc();
    /* nfc_scene_read_success_on_enter_mf_classic() + nfc_render_mf_classic_info() */
    FuriString* s = furi_string_alloc_set("\e#Mifare Classic 1K\n");
    furi_string_replace(s, "Mifare", "MIFARE");
    furi_string_cat(s, "UID:");
    for(size_t i = 0; i < sizeof(demo_uid); i++) furi_string_cat_printf(s, " %02X", demo_uid[i]);
    furi_string_cat_printf(s, "\nKeys Found: %u/%u", 32, 32);
    furi_string_cat_printf(s, "\nSectors Read: %u/%u", 16, 16);
    widget_add_text_scroll_element(widget, 0, 0, 128, 52, furi_string_get_cstr(s));
    widget_add_button_element(widget, GuiButtonTypeLeft, "Retry", noop_widget_cb, NULL);
    widget_add_button_element(widget, GuiButtonTypeRight, "More", noop_widget_cb, NULL);
    screen_draw_view(canvas, widget_get_view(widget));
}

SCREEN(nfc_extra_actions,
       .file = "nfc/extra_actions",
       .section = "nfc",
       .title = "Extra Actions",
       .menu_path = "NFC → Extra Actions",
       .scene = SCENES "nfc_scene_extra_actions.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu,
        "Read Specific Card Type",
        "MIFARE Classic Keys",
        "MIFARE Plus Keys",
        "MIFARE Ultralight C Keys",
        "MIFARE UL AES Keys",
        "Unlock NTAG/Ultralight",
        "Unlock SLIX-L",
        NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

/* nfc_data_generator_get_name() for every NfcDataGeneratorType, in enum order
 * (lib/nfc/helpers/nfc_data_generator.c). Copied rather than compiled because
 * that file pulls in the mbedtls submodule. */
static const char* const generator_names[] = {
    "Mifare Ultralight", "Mifare Ultralight EV1 11", "Mifare Ultralight EV1 H11",
    "Mifare Ultralight EV1 21", "Mifare Ultralight EV1 H21", "Mifare Ultralight C",
    "Mifare Ultralight AES", "NTAG203", "NTAG213", "NTAG215", "NTAG216", "NTAG I2C 1k",
    "NTAG I2C 2k", "NTAG I2C Plus 1k", "NTAG I2C Plus 2k", "Mifare Mini",
    "Mifare Classic 1k 4byte UID", "Mifare Classic 1k 7byte UID",
    "Mifare Classic 4k 4byte UID", "Mifare Classic 4k 7byte UID",
    "Mifare Plus SE 4byte UID", "Mifare Plus SE 7byte UID", "Mifare Plus S 2K 4byte UID",
    "Mifare Plus S 2K 7byte UID", "Mifare Plus S 4K 4byte UID", "Mifare Plus S 4K 7byte UID",
    "Mifare Plus X 2K 4byte UID", "Mifare Plus X 2K 7byte UID", "Mifare Plus X 4K 4byte UID",
    "Mifare Plus X 4K 7byte UID", "Mifare Plus EV1 2K 4b. UID", "Mifare Plus EV1 2K 7b. UID",
    "Mifare Plus EV1 4K 4b. UID", "Mifare Plus EV1 4K 7b. UID", "Mifare Plus EV2 2K 4b. UID",
    "Mifare Plus EV2 2K 7b. UID", "Mifare Plus EV2 4K 4b. UID", "Mifare Plus EV2 4K 7b. UID",
    "Texkom TK13", "Texkom TK17", "Texkom MMBIT",
};

SCREEN(nfc_add_manually,
       .file = "nfc/add_manually",
       .section = "nfc",
       .title = "Add Manually: card type",
       .menu_path = "NFC → Add Manually",
       .scene = SCENES "nfc_scene_set_type.c") {
    Submenu* submenu = submenu_alloc();
    submenu_add_item(submenu, "NFC-A 7-bytes UID", 0, spec_noop_submenu_cb, NULL);
    submenu_add_item(submenu, "NFC-A 4-bytes UID", 1, spec_noop_submenu_cb, NULL);
    for(size_t i = 0; i < COUNT_OF(generator_names); i++)
        submenu_add_item(submenu, generator_names[i], i + 2, spec_noop_submenu_cb, NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(nfc_mfkey_detect,
       .file = "nfc/mfkey_collecting",
       .section = "nfc",
       .title = "Extract MFC Keys: collecting nonces",
       .menu_path = "NFC → Extract MFC Keys",
       .scene = MFC_SCENES) {
    DetectReader* dr = detect_reader_alloc();
    detect_reader_set_nonces_max(dr, 10);
    uint8_t uid[sizeof(demo_uid)];
    memcpy(uid, demo_uid, sizeof(uid));
    detect_reader_set_uid(dr, uid, sizeof(uid));
    detect_reader_set_state(dr, DetectReaderStateReaderDetected);
    detect_reader_set_nonces_collected(dr, 4);
    screen_draw_view(canvas, detect_reader_get_view(dr));
}

SCREEN(nfc_mfkey_start,
       .file = "nfc/mfkey_start",
       .section = "nfc",
       .title = "Extract MFC Keys: waiting for the reader",
       .menu_path = "NFC → Extract MFC Keys",
       .scene = MFC_SCENES) {
    DetectReader* dr = detect_reader_alloc();
    detect_reader_set_nonces_max(dr, 10);
    uint8_t uid[sizeof(demo_uid)];
    memcpy(uid, demo_uid, sizeof(uid));
    detect_reader_set_uid(dr, uid, sizeof(uid));
    detect_reader_set_state(dr, DetectReaderStateStart);
    screen_draw_view(canvas, detect_reader_get_view(dr));
}

SCREEN(nfc_mfkey_nonces,
       .file = "nfc/mfkey_nonces_info",
       .section = "nfc",
       .title = "Extract MFC Keys: nonces saved",
       .menu_path = "NFC → Extract MFC Keys → Done",
       .scene = MFC_SCENES) {
    Widget* widget = widget_alloc();
    FuriString* s = furi_string_alloc();
    furi_string_printf(s, "Nonce pairs saved: %zu\n", (size_t)5);
    widget_add_string_element(widget, 0, 0, AlignLeft, AlignTop, FontPrimary, furi_string_get_cstr(s));
    widget_add_string_element(
        widget, 0, 12, AlignLeft, AlignTop, FontSecondary, "Authenticated sectors:");
    /* mfkey32_logger_get_params_data() */
    furi_string_set(s, "Sector 0, key A\nSector 1, key A\nSector 1, key B\n");
    widget_add_text_scroll_element(widget, 0, 22, 128, 42, furi_string_get_cstr(s));
    widget_add_button_element(widget, GuiButtonTypeCenter, "OK", noop_widget_cb, NULL);
    screen_draw_view(canvas, widget_get_view(widget));
}
