#include <math.h>
#include <Arduino.h>
#include "controller.h"

Ball_On_Beam_Controller::Ball_On_Beam_Controller(float Kp, float Ki, float Kd, int stepPin,int dirPin, int enPin, int IRPin):
    Kp_(Kp),
    Kd_(Kd),
    Ki_(Ki),
    stepper_motor(stepPin, dirPin, enPin),
    distance_sensor_(IRPin)
    {
    // nothing
}

void Ball_On_Beam_Controller::setup_run(){
    distance_sensor_.IR_sensor_setup_code();
    stepper_motor.Stepper_Interface_setup_run();
}

void Ball_On_Beam_Controller::run_once(long const &curr_runtime){
    update_state();
    update_errors(curr_runtime);
    float theta = calculate_theta_from_rdot2(calculate_r_dot2());
    // Serial.print("Theta: ");
    // Serial.print(theta);
    // Serial.print("|    ");
    stepper_motor.achieve_angle(theta);
};

float Ball_On_Beam_Controller::calculate_r_dot2(){
    return Kp_*error_ + Kd_*diff_error_ + Ki_*integral_error_;
    // Serial.print("Kp_term: ");
    // Serial.print(Kp_*error_ );
    // Serial.print("|    ");
    // Serial.print("Kd_term: ");
    // Serial.print(Kd_*diff_error_ );
    // Serial.print("|    ");
};

float Ball_On_Beam_Controller::calculate_theta_from_rdot2(float rdot2){
    // Serial.print("rodt2: ");
    // Serial.print(rdot2);
    // Serial.print("|    ");
    float alpha_p45 = 0.7853981633974483 + asin(0.0019513615843891072*(-rdot2));/* M_PI/4 + asin(0.0019513615843891072*rdot2)*/ 
    if (isnan(alpha_p45)){
        return 0.;
    }
    // return 135 - acos((1.4142135623730951 - 180./M_PI*(2* cos(alpha_p45))/sqrt(6 - 5.656854249492381*cos(alpha_p45))) + acos(sqrt(6 - 5.656854249492381*cos(alpha_p45))/2));
    return 2*(alpha_p45*180./M_PI - 45.);
};

void Ball_On_Beam_Controller::update_state(){
    distance_sensor_.get_state(curr_distance_, curr_speed_);
    // Serial.print("Distance: ");
    // Serial.print(curr_distance_);
    // Serial.print("|    ");
    // Serial.print("Speed: ");
    // Serial.print(curr_speed_);
    // Serial.print("|    ");
};

void Ball_On_Beam_Controller::update_errors(long const &curr_runtime){
    error_ = target_value_ - curr_distance_;
    diff_error_ = -curr_speed_;
    integral_error_ += 0.5*(error_ + last_error_)*(curr_runtime - last_runtime_);

    last_error_ = error_;
    last_runtime_ = curr_runtime;
};

void Ball_On_Beam_Controller::set_target_value(float new_target_value){
    target_value_ = new_target_value;
}