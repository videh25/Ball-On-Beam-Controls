#include <Arduino.h>
#include "ir_sensor_interface.h"

IR_Sensor_Interface::IR_Sensor_Interface(int irPin):
    IR_Pin_(irPin){
    // nothing here
}

void IR_Sensor_Interface::IR_sensor_setup_code(){
    pinMode (IR_Pin_, INPUT);
    
    #ifdef ARDUINO
      analogReference(DEFAULT);
    #endif
}

void IR_Sensor_Interface::update_values(){
    for (int i = 0; i < 3; i++){
        time_values_[i] = ((double)micros());
        distance_values_[i] = 27.728 * pow(map(analogRead(IR_Pin_), 0, 1023, 0, 5000)/1000.0, -1.2045);
    }
}

void IR_Sensor_Interface::get_state(float &dist_var, float &speed_var){
    update_values();
    float sum = 0; 
    double t0 = time_values_[0];
    for (int i = 0; i < 3; i++){
        sum += distance_values_[i];
        time_values_[i] = (time_values_[i] - t0)/1E6;
    }
    dist_var=sum/3;


    // Quadratic Fitting
    double a = (time_values_[1]*distance_values_[0] - time_values_[2]*distance_values_[0] - time_values_[1]*distance_values_[2] + time_values_[2]*distance_values_[1])/(time_values_[1]*time_values_[2]*(time_values_[1] - time_values_[2]));
    double b = -(time_values_[1]*time_values_[1]*distance_values_[0] - time_values_[2]*time_values_[2]*distance_values_[0] - time_values_[1]*time_values_[1]*distance_values_[2] + time_values_[2]*time_values_[2]*distance_values_[1])/(time_values_[1]*time_values_[2]*(time_values_[1] - time_values_[2]));

    Serial.print("t1t2t3:");
    Serial.print(" ");
    Serial.print(time_values_[0]);
    Serial.print(" ");
    Serial.print(time_values_[1]);
    Serial.print(" ");
    Serial.println(time_values_[2]);
    Serial.print("AB:");
    Serial.print(" ");
    Serial.print(a);
    Serial.print(" ");
    Serial.print(b);
    
    
    speed_var=(float)(2*a*time_values_[2]+b);
}