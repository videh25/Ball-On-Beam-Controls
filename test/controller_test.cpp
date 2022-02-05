#include <Arduino.h>
#include "controller.h"
#include <Arduino.h>
#include "controller.h"

#define DIR_PIN 2
#define STEP_PIN 5
#define EN_PIN 8
#define IR_PIN A0
#define LOOP_HZ 1
// #define LOOP_HZ 100

Ball_On_Beam_Controller controller(10., 0. , 0., STEP_PIN, DIR_PIN, EN_PIN, IR_PIN);

long pepe1 = millis();
long pepe2;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    controller.setup_run();
    controller.set_target_value((float)15);
}

void loop() {
    // put your main code here, to run repeatedly:
    pepe2 = millis();

    if ((pepe2 - pepe1) > (1E3F/LOOP_HZ)){
        controller.run_once(pepe2);
        pepe1 = pepe2;
    }
}