#include <Arduino.h>
#include "stepper_interface.h"

#define DIR_PIN 2
#define STEP_PIN 5
#define EN_PIN 8

Stepper_Interface stepper(STEP_PIN, DIR_PIN, EN_PIN);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    stepper.Stepper_Interface_setup_run();
}

void loop() {
    // put your main code here, to run repeatedly:
    stepper.achieve_angle(30.);
    delay(500);
    stepper.achieve_angle(0.);
    delay(500);
    stepper.achieve_angle(-30.);
    delay(500);
    stepper.achieve_angle(0.);
    delay(500);
}