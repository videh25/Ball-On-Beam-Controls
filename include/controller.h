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

        // pid gains
        float Kp_;
        float Kd_;
        float Ki_;

        // errors
        float error_;
        float diff_error_;
        float integral_error_;
        float last_error_;
        long last_runtime_;

        // loop constants
        float target_value_;



        float curr_distance_;
        float curr_speed_;

        float theta_;

        
        // link lengths and physical properties
        float d1_;
        float L_;
        float R_;
        float R1_;
        float g_;

    public:
        Ball_On_Beam_Controller();
        
        void set_target_value(float new_target_value);

        float calculate_r_dot2();
        float calculate_theta_from_rdot2(float rdot2);

        void update_state();
        void update_errors(long const &curr_runtime);

        void run_once(long const &curr_runtime);
};

#endif