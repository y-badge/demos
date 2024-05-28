#include "Arduino.h"
#include "yboard.h"

void setup() {
    Serial.begin(9600);
    yboard.setup();
}

void loop() {}
