#include <math.h>
#include "controller.h"

Ball_On_Beam_Controller::Ball_On_Beam_Controller(float Kp, float Ki, float Kd, int stepPin,int dirPin, int enPin):
    Kp_(Kp),
    Kd_(Kd),
    Ki_(Ki),
    stepper_motor(stepPin, dirPin, enPin)
    {
    // nothing
}

void Ball_On_Beam_Controller::run_once(long const &curr_runtime){
    update_state();
    update_errors(curr_runtime);
    stepper_motor.achieve_angle(calculate_theta_from_rdot2(calculate_r_dot2()));
};

float Ball_On_Beam_Controller::calculate_r_dot2(){
    return Kp_*error_ + Kd_*diff_error_ + Ki_*integral_error_;
};

float Ball_On_Beam_Controller::calculate_theta_from_rdot2(float rdot2){
    float alpha_p45 = 0.7853981633974483 + asin(0.0019513615843891072*rdot2);/* M_PI/4 + asin(0.0019513615843891072*rdot2)*/ 
    
    return 135 - acos((1.4142135623730951 - 180./M_PI*(2* cos(alpha_p45))/sqrt(6 - 5.656854249492381*cos(alpha_p45))) + acos(sqrt(6 - 5.656854249492381*cos(alpha_p45))/2));
};

void Ball_On_Beam_Controller::update_state(){
    // curr_distance_ = distance_sensor_.get_distance();
    // curr_speed_ = distance_sensor_.get_speed();
};

void Ball_On_Beam_Controller::update_errors(long const &curr_runtime){
    error_ = target_value_ - curr_distance_;
    diff_error_ = -curr_speed_;
    integral_error_ += 0.5*(error_ + last_error_)*(curr_runtime - last_runtime_);

    last_error_ = error_;
};