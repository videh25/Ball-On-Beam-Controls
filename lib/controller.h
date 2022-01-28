// Ball on Beam Controller
#include "ir_sensor_interface.h"
#include "stepper_interface.h"


#ifndef __BALL_ON_BEAM_CONTROLLER__
#define __BALL_ON_BEAM_CONTROLLER__

class Ball_On_Beam_Controller
{
    // Methods and Function of the Controller
    private:
        IR_Sensor_Interface distance_sensor_;
        Stepper_Interface stepper_motor;

        float Kp_;
        float Kd_;
        float Ki_;

        float last_error_;
        float integral_error_;

        long last_run_time_;

    public:
        Ball_On_Beam_Controller();
        
        float calculate_r_dot2();
        float calculate_theta_from_rdot2();

        void run_once(long curr_runtime);
};

#endif