/* Infrared screens: applications/main/infrared */
#include "screen.h"
#include "spec_util.h"

#define SCENES "applications/main/infrared/scenes/"

static void noop_panel_cb(void* context, uint32_t index, InputType type) {
    (void)context;
    (void)index;
    (void)type;
}

static void noop_button_menu_cb(void* context, int32_t index, InputType type) {
    (void)context;
    (void)index;
    (void)type;
}

SCREEN(infrared_menu,
       .file = "infrared/menu",
       .section = "infrared",
       .title = "Infrared main menu",
       .menu_path = "Infrared",
       .scene = SCENES "infrared_scene_start.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(
        submenu, "Universal Remotes", "Learn New Remote", "Saved Remotes", "GPIO Settings", NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(infrared_universal,
       .file = "infrared/universal_remotes",
       .section = "infrared",
       .title = "Universal Remotes",
       .menu_path = "Infrared → Universal Remotes",
       .scene = SCENES "infrared_scene_universal.c") {
    Submenu* submenu = submenu_alloc();
    spec_submenu_items(submenu, "TVs", "Audio", "Projectors", "LEDs", "Fans", "ACs", NULL);
    screen_draw_view(canvas, submenu_get_view(submenu));
}

SCREEN(infrared_universal_tv,
       .file = "infrared/universal_tv",
       .section = "infrared",
       .title = "Universal TV remote",
       .menu_path = "Infrared → Universal Remotes → TVs",
       .scene = SCENES "infrared_scene_universal_tv.c") {
    /* same calls as infrared_scene_universal_tv_on_enter() */
    ButtonPanel* bp = button_panel_alloc();
    button_panel_reserve(bp, 2, 3);
    uint32_t i = 0;
    button_panel_add_item(
        bp, i++, 0, 0, 6, 16, &I_power_19x20, &I_power_hover_19x20, noop_panel_cb, NULL);
    button_panel_add_icon(bp, 4, 38, &I_power_text_24x5);
    button_panel_add_item(
        bp, i++, 1, 0, 39, 16, &I_mute_19x20, &I_mute_hover_19x20, noop_panel_cb, NULL);
    button_panel_add_icon(bp, 39, 38, &I_mute_text_19x5);
    button_panel_add_icon(bp, 0, 66, &I_ch_text_31x34);
    button_panel_add_icon(bp, 35, 66, &I_vol_tv_text_29x34);
    button_panel_add_item(
        bp, i++, 1, 1, 38, 53, &I_volup_24x21, &I_volup_hover_24x21, noop_panel_cb, NULL);
    button_panel_add_item(
        bp, i++, 0, 1, 3, 53, &I_ch_up_24x21, &I_ch_up_hover_24x21, noop_panel_cb, NULL);
    button_panel_add_item(
        bp, i++, 1, 2, 38, 91, &I_voldown_24x21, &I_voldown_hover_24x21, noop_panel_cb, NULL);
    button_panel_add_item(
        bp, i++, 0, 2, 3, 91, &I_ch_down_24x21, &I_ch_down_hover_24x21, noop_panel_cb, NULL);
    button_panel_add_label(bp, 25, 10, FontPrimary, "TV");
    screen_draw_view(canvas, button_panel_get_view(bp));
}

SCREEN(infrared_learn,
       .file = "infrared/learn",
       .section = "infrared",
       .title = "Learn New Remote: waiting for a signal",
       .menu_path = "Infrared → Learn New Remote",
       .scene = SCENES "infrared_scene_learn.c") {
    Popup* popup = popup_alloc();
    popup_set_icon(popup, 0, 32, &I_InfraredLearnShort_128x31);
    popup_set_header(popup, NULL, 0, 0, AlignCenter, AlignCenter);
    popup_set_text(
        popup, "Point the remote at IR port\nand push the button", 5, 10, AlignLeft, AlignCenter);
    screen_draw_view(canvas, popup_get_view(popup));
}

SCREEN(infrared_learn_success,
       .file = "infrared/learn_success",
       .section = "infrared",
       .title = "Learn New Remote: signal received",
       .menu_path = "Infrared → Learn New Remote → (button pressed)",
       .scene = SCENES "infrared_scene_learn_success.c") {
    /* NEC, address 0x04, command 0x08: 2 hex digits each, so the label
     * x offset is 63 + (7 - 2) * 3 */
    DialogEx* d = dialog_ex_alloc();
    dialog_ex_set_header(d, "NEC", 95, 7, AlignCenter, AlignCenter);
    dialog_ex_set_text(d, "A: 0x04\nC: 0x08\n", 63 + (7 - 2) * 3, 34, AlignLeft, AlignCenter);
    dialog_ex_set_left_button_text(d, "Retry");
    dialog_ex_set_right_button_text(d, "Save");
    dialog_ex_set_center_button_text(d, "Send");
    dialog_ex_set_icon(d, 0, 1, &I_DolphinReadingSuccess_59x63);
    screen_draw_view(canvas, dialog_ex_get_view(d));
}

SCREEN(infrared_remote,
       .file = "infrared/remote",
       .section = "infrared",
       .title = "Saved remote",
       .menu_path = "Infrared → Saved Remotes → (remote)",
       .scene = SCENES "infrared_scene_remote.c") {
    ButtonMenu* bm = button_menu_alloc();
    static const char* const names[] = {"Power", "Vol_up", "Vol_dn", "Mute", "Ch_next", "Ch_prev"};
    for(size_t i = 0; i < COUNT_OF(names); i++)
        button_menu_add_item(
            bm, names[i], i, noop_button_menu_cb, ButtonMenuItemTypeCommon, NULL);
    button_menu_add_item(bm, "+", -1, noop_button_menu_cb, ButtonMenuItemTypeControl, NULL);
    button_menu_add_item(bm, "Edit", -2, noop_button_menu_cb, ButtonMenuItemTypeControl, NULL);
    button_menu_set_header(bm, "Samsung_TV");
    button_menu_set_selected_item(bm, 0);
    screen_draw_view(canvas, button_menu_get_view(bm));
}
