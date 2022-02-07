#include <Arduino.h>
#include "ir_sensor_interface.h"

#define IR_PIN A0

IR_Sensor_Interface IR(IR_PIN);
float dist;
float speed;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    IR.IR_sensor_setup_code();
}

void loop() {
    // put your main code here, to run repeatedly:
    delay(20);
    IR.get_state(dist, speed);
    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.print("|    Speed: ");
    Serial.println(speed);
}