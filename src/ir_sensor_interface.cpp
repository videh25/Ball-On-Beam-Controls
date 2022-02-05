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
    for (int i = 0; i < 5; i++){
        time_values_[i] = ((double)micros());
        distance_values_[i] = 27.728 * pow(map(analogRead(IR_Pin_), 0, 1023, 0, 5000)/1000.0, -1.2045);
    }
}

void IR_Sensor_Interface::get_state(float &dist_var, float &speed_var){
    update_values();
    //float sum = 0; 
    // for (int i = 0; i < 5; i++){
    //     sum += distance_values_[i];
    //     // time_values_[i] = (time_values_[i] - t0)/1E6;
    // }
    dist_var=(distance_values_[2]+distance_values_[3]+distance_values_[4])/3 ;
    speed_var=(distance_values_[4]-distance_values_[1])/(3*(time_values_[4]-time_values_[3]))*1E6;
    // float dist1 = sum/3;

    // update_values();
    // sum = 0; 
    // double t2 = time_values_[2];
    // for (int i = 0; i < 3; i++){
    //     sum += distance_values_[i];
    //     // time_values_[i] = (time_values_[i] - t0)/1E6;
    // }
    
    // float dist2 = sum/3;   
    
    //dist_var = dist2;
    //speed_var=(float)((dist2-dist1)/(t2-t1)*1E6);
}