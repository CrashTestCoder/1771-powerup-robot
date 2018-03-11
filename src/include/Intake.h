/* * * * * * * * * * * * * *
 *         Intake.h        *
 * by Justin DeSimpliciis  *
 * * * * * * * * * * * * * */

#ifndef INTAKE_H_
#define INTAKE_H_

#include "WPILib.h"
#include <ctre/Phoenix.h>

#include <Definitions.h>

class Intake {
private:
    Solenoid flipper;
    TalonSRX rin, lin;
    
    TalonSRX arm_pivot;
    
    // Might switch to encoder for ease
    frc::Encoder pivot_enc;
    //AnalogInput pivot_pot;
    
public:
    Intake(int arm_pivot_port, int flipper_port, int rin_port, int lin_port, int arm_enc_a, int arm_enc_b); // use def directly?
    
    void SetArms(bool state);
    
    void SetIntakeWheels(double rate);
    void SetFlipper(bool flip);
    
    // Should be an encoder value representing arm position; returns 0 if not at point and 1 if at point
    int SetPivotArm(double pos);
    
};

#endif // INTAKE_H_
