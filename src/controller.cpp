#include <math.h>
#include "controller.h"

void Ball_On_Beam_Controller::run_once(long const &curr_runtime){
    update_state();
    update_errors(curr_runtime);
    theta_ = calculate_theta_from_rdot2(calculate_r_dot2())*180./M_PI;
    stepper_motor.achieve_angle(theta_);
};

float Ball_On_Beam_Controller::calculate_r_dot2(){
    return Kp_*error_ + Kd_*diff_error_ + Ki_*integral_error_;
};

float Ball_On_Beam_Controller::calculate_theta_from_rdot2(float rdot2){
    return asin(0.5*(rdot2*L_)/(g_*R1_*R1_*d1_)*(0.4*R_*R_ + R1_*R1_) + 1);
};

void Ball_On_Beam_Controller::update_state(){
    curr_distance_ = distance_sensor_.get_distance();
    curr_speed_ = distance_sensor_.get_speed();
};

void Ball_On_Beam_Controller::update_errors(long const &curr_runtime){
    error_ = target_value_ - curr_distance_;
    diff_error_ = -curr_speed_;
    integral_error_ += 0.5*(error_ + last_error_)*(curr_runtime - last_runtime_);

    last_error_ = error_;
};