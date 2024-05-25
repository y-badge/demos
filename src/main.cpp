#include "yboardv2.h"

#include "hardware_test/hardware_test.h"
#include "light_show/light_show.h"
#include "wifi_sniffer/wifi_sniffer.h"

YBoardv2 yboard;

void setup() {
    // wifi_sniffer_init(&yboard);
    // hardware_test_init(&yboard);
    light_show_init(&yboard);
}

void loop() {
    // wifi_sniffer_loop();
    // hardware_test_loop();
    light_show_loop();
}
