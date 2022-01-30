#include <Arduino.h>
#include "stepper_interface.h"

Stepper_Interface::Stepper_Interface(int stepPin,int dirPin, int enPin):
    stepPin_(stepPin),
    dirPin_(dirPin),
    enPin_(enPin),
    angle_(0.)
    {
    // nothing
};

void Stepper_Interface::Stepper_Interface_setup_run(){
    pinMode(stepPin_, OUTPUT);
    pinMode(dirPin_, OUTPUT);
    pinMode(enPin_,OUTPUT);
    digitalWrite(enPin_,LOW);
};

void Stepper_Interface::achieve_angle(float theta){
    theta = theta - fmodf(theta,1.8);
    Serial.print("Theta:");
    Serial.println(theta);
    while (angle_!=theta){
        if (abs(angle_)>=68){
            break;
        }
        float haha_angle = theta - angle_;
        // Serial.print("HAHA: ");
        // Serial.println(haha_angle);
        // Serial.println("Yahaa atka h0");
        if (haha_angle < 0 ){
            digitalWrite(dirPin_, LOW);
            int step = map(haha_angle, 0, 360, 0, 200);
            Serial.print("Step: ");
            Serial.println(step);
            // Serial.println(step);
            // Serial.print("Yahaa atka h1");
            for (int i = 0; i > step; i--){
                digitalWrite(stepPin_, HIGH);
                delayMicroseconds(1500);
                digitalWrite(stepPin_, LOW);
                delayMicroseconds(1500);
                // Serial.print("Yahaa atka h2");
            }
            angle_ = theta;
        }
        else{
            digitalWrite(dirPin_, HIGH);
            int step = map(haha_angle, 0, 360, 0, 200);
            Serial.print("Step: ");
            Serial.println(step);
            // Serial.println("Yahaa atka h3");
            // Serial.println(step);
            for (int i = 0; i < step; i++){
                digitalWrite(stepPin_, HIGH);
                delayMicroseconds(1500);
                digitalWrite(stepPin_, LOW);
                delayMicroseconds(1500);
                // Serial.println("Yahaa atka h4");
            }
            angle_ = theta;
        }
    }
}
