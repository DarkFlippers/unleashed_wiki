#pragma once
/* Small helpers shared by screen specs. They only call public module APIs,
 * the same way the firmware scenes do. */
#include "screen.h"
#include <gui/modules/submenu.h>
#include <gui/modules/variable_item_list.h>
#include <gui/modules/widget.h>
#include <gui/modules/popup.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/text_box.h>
#include <gui/modules/text_input.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/button_menu.h>
#include <gui/modules/button_panel.h>
#include <gui/modules/loading.h>

/* submenu_add_item() for each label (NULL-terminated), indices 0..n-1 */
void spec_submenu_items(Submenu* submenu, ...);

/* variable_item_list_add() + set_current_value_index() + set_current_value_text() */
VariableItem* spec_var_item(
    VariableItemList* list,
    const char* label,
    uint8_t values_count,
    uint8_t index,
    const char* value_text);

void spec_noop_submenu_cb(void* ctx, uint32_t index);
