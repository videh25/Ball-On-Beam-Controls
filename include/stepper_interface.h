// Stepper Motor Interface

#ifndef __STEPPER_INTERFACE__
#define __STEPPER_INTERFACE__

class Stepper_Interface
{
    // Methods and Function of the Stepper Motor Interface
    private:
        float angle_;
        int enPin_;
        int stepPin_;
        int dirPin_;
        
    public:
        void achieve_angle(float theta);
        Stepper_Interface(int stepPin,int dirPin, int enPin);
        void Stepper_Interface_setup_run();
};

#endif