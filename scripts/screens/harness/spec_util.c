#include "spec_util.h"
#include <stdarg.h>

void spec_noop_submenu_cb(void* ctx, uint32_t index) {
    (void)ctx;
    (void)index;
}

void spec_submenu_items(Submenu* submenu, ...) {
    va_list args;
    va_start(args, submenu);
    uint32_t i = 0;
    for(const char* label = va_arg(args, const char*); label; label = va_arg(args, const char*)) {
        submenu_add_item(submenu, label, i++, spec_noop_submenu_cb, NULL);
    }
    va_end(args);
}

static void spec_noop_var_cb(VariableItem* item) {
    (void)item;
}

VariableItem* spec_var_item(
    VariableItemList* list,
    const char* label,
    uint8_t values_count,
    uint8_t index,
    const char* value_text) {
    VariableItem* item = variable_item_list_add(list, label, values_count, spec_noop_var_cb, NULL);
    variable_item_set_current_value_index(item, index);
    variable_item_set_current_value_text(item, value_text);
    return item;
}
