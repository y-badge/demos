#ifndef HARDWARE_TEST_H
#define HARDWARE_TEST_H

#include "Arduino.h"
#include "yboardv2.h"

// Required functions
void hardware_test_init(YBoard *yb);
void hardware_test_loop();

int get_brightness();
bool check_switches();
void play_note(unsigned int freq, unsigned long duration);

#endif /* HARDWARE_TEST_H */
