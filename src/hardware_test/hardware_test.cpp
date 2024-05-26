#include "hardware_test.h"
#include "colors.h"

static YBoard *yboard;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

void hardware_test_init(YBoard *yb) {
    Serial.begin(9600);
    yboard = yb;
    yboard->setup();
    yboard->set_led_brightness(10);

    if (yboard->get_type() == YBoard::BoardType::v3) {
        YBoardV3 *v3 = (YBoardV3 *)yboard;
        v3->play_song_from_sd("/ZTJB.mp3");
    }
}

/*
 * This function tests all of the features of the badge.
 * It will display different colors depending on which button is pressed.
 * It will also play different notes depending on which button is pressed IF at least one of the two
 * switches is on It will also change the brightness of the LEDs depending on the position of the
 * knob.
 */
void hardware_test_loop() {
    unsigned long currentMillis = millis();

    // Clear some of the LEDs
    yboard->set_led_color(0, 0, 0, 0);
    yboard->set_led_color(1, 0, 0, 0);
    yboard->set_led_color(2, 0, 0, 0);
    yboard->set_led_color(3, 0, 0, 0);
    yboard->set_led_color(4, 0, 0, 0);

    if (yboard->get_button(1)) {
        yboard->set_led_color(0, 255, 0, 0);

        if (yboard->get_type() == YBoard::BoardType::v3) {
            YBoardV3 *v3 = (YBoardV3 *)yboard;
            v3->loop_speaker();
        } else if (yboard->get_type() == YBoard::BoardType::v2) {
            YBoardV2 *v2 = (YBoardV2 *)yboard;
            v2->play_note(440, 10);
        }
    }
    if (yboard->get_button(2)) {
        yboard->set_led_color(1, 255, 0, 0);
    }
    if (yboard->get_button(3)) {
        yboard->set_led_color(2, 255, 0, 0);
    }
    if (yboard->get_switch(1)) {
        yboard->set_led_color(3, 255, 0, 0);
    }
    if (yboard->get_switch(2)) {
        yboard->set_led_color(4, 255, 0, 0);
    }
    yboard->set_led_color(5, map(yboard->get_knob(), 0, 100, 0, 255), 0, 0);

    // Do version 3 specific tests
    if (yboard->get_type() == YBoard::BoardType::v3) {
        YBoardV3 *v3 = (YBoardV3 *)yboard;

        if (currentMillis - previousMillis1 >= 100) {
            previousMillis1 = currentMillis;

            float x, y, z;
            v3->get_accelerometer(&x, &y, &z);
            yboard->set_led_color(6, map(x, -1050, 1050, 0, 255), 0, 0);
            yboard->set_led_color(7, map(y, -1050, 1050, 0, 255), 0, 0);
            yboard->set_led_color(8, map(z, -1050, 1050, 0, 255), 0, 0);
            // Serial.printf("x: %f, y: %f, z: %f\n", x, y, z);
        }

        if (currentMillis - previousMillis2 >= 1000) {
            previousMillis2 = currentMillis;

            float temp, humidity;
            v3->get_temperature(&temp, &humidity);
            if (temp > 28) {
                yboard->set_led_color(9, 255, 0, 0);
            } else {
                yboard->set_led_color(9, 0, 0, 0);
            }

            if (humidity > 50) {
                yboard->set_led_color(10, 255, 0, 0);
            } else {
                yboard->set_led_color(10, 0, 0, 0);
            }
            Serial.printf("temp: %f, humidity: %f\n", temp, humidity);
        }
    }
}
