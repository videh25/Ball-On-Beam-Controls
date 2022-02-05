#include <Arduino.h>
#include "controller.h"
#include <Arduino.h>
#include "controller.h"


#define KP 3. //4.
#define KD 4.2 //0.005
#define KI 0.
#define DIR_PIN 2
#define STEP_PIN 5
#define EN_PIN 8
#define IR_PIN A0
#define LOOP_HZ 50.
// #define LOOP_HZ 100

Ball_On_Beam_Controller controller(KP, KI , KD, STEP_PIN, DIR_PIN, EN_PIN, IR_PIN);

long pepe1 = millis();
long pepe2;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    controller.setup_run();
    controller.set_target_value(20.);
    // Serial.println(controller.Kp_);
    Serial.println("10 secs to turn on motor:");
    for (int i = 0; i < 5; i++){
        Serial.print("TICK TICK ");
        Serial.println(i+1);
        delay(1000);
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    pepe2 = millis();

    if ((pepe2 - pepe1) > (1E3F/LOOP_HZ)){
        controller.run_once(pepe2);
        //Serial.print("|    Time: ");
        //Serial.println(pepe2 - pepe1);
        pepe1 = pepe2;
    }
}