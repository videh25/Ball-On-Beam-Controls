// Interface for IR Sensor

#ifndef __IR_SENSOR_INTERFACE__
#define __IR_SENSOR_INTERFACE__

class IR_Sensor_Interface
{
    // Methods and Function of the IR Sensor Interface
    private:
        int IR_Pin_;
        float distance_values_[3];
        double time_values_[3];

    public:
        void get_state(float &dist_var, float &speed_var);
        void IR_sensor_setup_code();
        IR_Sensor_Interface (int irPin);
        void update_values();
};

#endif