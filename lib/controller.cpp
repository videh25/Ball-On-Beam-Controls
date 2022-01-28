#include "controller.h"

void Ball_On_Beam_Controller::run_once(long curr_runtime){
    float dist_ = distance_sensor_.get_distance();
    float speed_ = distance_sensor_.get_speed();

    float curr_error = 15. - dist_;
    long dt_ = curr_runtime - last_run_time_;
    last_run_time_ = curr_runtime;

    float differential_error = (curr_error - last_error_)/dt_;
    float integral_error = (curr_error + last_error_)*dt_/2;
}