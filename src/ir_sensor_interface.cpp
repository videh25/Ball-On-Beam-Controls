#include <Arduino.h>
#include "ir_sensor_interface.h"

IR_Sensor_Interface::IR_Sensor_Interface(int irPin):
    IR_Pin_(irPin){
    // nothing here
    speed_counter = 0;
    last_dist_var_4speed = 0;
}

void IR_Sensor_Interface::IR_sensor_setup_code(){
    pinMode (IR_Pin_, INPUT);
    #ifdef ARDUINO
      analogReference(DEFAULT);
    #endif
}

void IR_Sensor_Interface::update_values(){
    for (int i = 0; i < 5; i++){
        // time_values_[i] = ((double)micros());
        voltage_values_[i] = analogRead(IR_Pin_);
    }
}

void IR_Sensor_Interface::get_state(float &dist_var, float &speed_var){
    update_values();
    float sum = 0; 
    for (int i = 0; i < 5; i++){
        sum += voltage_values_[i];
        // time_values_[i] = (time_values_[i] - t0)/1E6;
    }

    dist_var = 27.728*pow(map(sum/5., 0, 1023, 0, 5000)/1000.0, -1.2045);

    if (speed_counter > 10){
        curr_return_speed = dist_var - last_dist_var_4speed;
        if (abs(curr_return_speed)<0.1){curr_return_speed=0;}
        curr_return_speed = constrain(curr_return_speed,-5,5);

        last_dist_var_4speed = dist_var;
        speed_counter = 0;
    }else{
        speed_counter++;
    }

    speed_var = curr_return_speed;
     //limit the max size of the derivative of error to reduce high freq
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