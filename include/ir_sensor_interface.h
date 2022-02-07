// Interface for IR Sensor

#ifndef __IR_SENSOR_INTERFACE__
#define __IR_SENSOR_INTERFACE__

class IR_Sensor_Interface
{
    // Methods and Function of the IR Sensor Interface
    private:
        int IR_Pin_;
        float voltage_values_[5];
        double time_values_[5];
        unsigned int speed_counter;
        float curr_return_speed;
        float last_dist_var_4speed;

    public:
        void get_state(float &dist_var, float &speed_var);
        void IR_sensor_setup_code();
        IR_Sensor_Interface (int irPin);
        void update_values();
};

#endif