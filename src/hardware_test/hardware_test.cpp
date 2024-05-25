#include "hardware_test.h"

static YBoard *yboard;

void hardware_test_init(YBoard *yb) {
    Serial.begin(9600);
    yboard = yb;
    yboard->setup();
}

/*
 * This function tests all of the features of the badge.
 * It will display different colors depending on which button is pressed.
 * It will also play different notes depending on which button is pressed IF at least one of the two
 * switches is on It will also change the brightness of the LEDs depending on the position of the
 * knob.
 */
void hardware_test_loop() {
    if (yboard->get_button(1)) {
        while (yboard->get_button(1)) {
            yboard->set_all_leds_color(255, 0, 0);
            yboard->set_led_brightness(get_brightness());
            if (check_switches()) {
                play_note(NOTE_C4, 10);
                delay(10);
            }
        }
    } else if (yboard->get_button(2)) {
        while (yboard->get_button(2)) {
            yboard->set_all_leds_color(255, 255, 0);
            yboard->set_led_brightness(get_brightness());
            if (check_switches()) {
                play_note(NOTE_D4, 10);
                delay(10);
            }
        }
    } else if (yboard->get_button(3)) {
        while (yboard->get_button(3)) {
            yboard->set_all_leds_color(0, 255, 0);
            yboard->set_led_brightness(get_brightness());
            if (check_switches()) {
                play_note(NOTE_E4, 10);
                delay(10);
            }
        }
    } else {
        yboard->set_all_leds_color(255, 255, 255);
        yboard->set_led_brightness(get_brightness());
    }
}

// This function converts the knob's output (1-100) to a brightness value (0-255)
int get_brightness() { return map(yboard->get_knob(), 0, 100, 0, 255); }

// This function checks if either of the switches are on
bool check_switches() { return yboard->get_switch(1) || yboard->get_switch(2); }

void play_note(unsigned int freq, unsigned long duration) {
    if (yboard->get_type() == YBoard::BoardType::v2) {
        YBoardV2 *v2 = (YBoardV2 *)yboard;
        v2->play_note(freq, duration);
    } else {
        Serial.println("This function is not implemented on version 3.");
    }
}
