/* GPIO screens: applications/main/gpio */
#include "screen.h"
#include "spec_util.h"

#include <gpio/views/gpio_usb_uart.h>
#include <gpio/usb_uart_bridge.h>

#define SCENES "applications/main/gpio/scenes/"

SCREEN(gpio_menu,
       .file = "gpio/menu",
       .section = "gpio",
       .title = "GPIO main menu",
       .menu_path = "GPIO",
       .scene = SCENES "gpio_scene_start.c") {
    VariableItemList* list = variable_item_list_alloc();
    variable_item_list_add(list, "USB-UART Bridge", 0, NULL, NULL);
    variable_item_list_add(list, "GPIO Manual Control", 0, NULL, NULL);
    spec_var_item(list, "5V on GPIO", 2, 0, "OFF");
    screen_draw_view(canvas, variable_item_list_get_view(list));
}

SCREEN(gpio_usb_uart,
       .file = "gpio/usb_uart",
       .section = "gpio",
       .title = "USB-UART Bridge",
       .menu_path = "GPIO → USB-UART Bridge",
       .scene = SCENES "gpio_scene_usb_uart.c") {
    GpioUsbUart* uu = gpio_usb_uart_alloc();
    UsbUartConfig cfg = {.vcp_ch = 0, .uart_ch = 0, .flow_pins = 0, .baudrate_mode = 0};
    /* two updates so the counters are shown without the "active" arrows */
    UsbUartState st = {.rx_cnt = 18734, .tx_cnt = 412, .baudrate_cur = 115200};
    gpio_usb_uart_update_state(uu, &cfg, &st);
    gpio_usb_uart_update_state(uu, &cfg, &st);
    screen_draw_view(canvas, gpio_usb_uart_get_view(uu));
}

SCREEN(gpio_usb_uart_config,
       .file = "gpio/usb_uart_config",
       .section = "gpio",
       .title = "USB-UART Bridge settings",
       .menu_path = "GPIO → USB-UART Bridge → Config",
       .scene = SCENES "gpio_scene_usb_uart_config.c") {
    VariableItemList* list = variable_item_list_alloc();
    spec_var_item(list, "USB Channel", 2, 0, "0 (CLI)");
    spec_var_item(list, "Baudrate", 12 + 1, 0, "Host");
    spec_var_item(list, "UART Pins", 2, 0, "13,14");
    spec_var_item(list, "RTS/DTR Pins", 4, 0, "None");
    spec_var_item(list, "DE/RE Pin", 2, 0, "None");
    screen_draw_view(canvas, variable_item_list_get_view(list));
}
