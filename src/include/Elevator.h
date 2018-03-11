/* * * * * * * * * * * * * *
 *        Elevator.h       *
 * by Justin DeSimpliciis  *
 * * * * * * * * * * * * * */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <ctre/Phoenix.h>
#include <Definitions.h>
#include <Intake.h>

class Elevator {
private:
    TalonSRX elvtr;
    Encoder elvtr_enc;
    
    // Elevator PI control
    double change;
    int error, desired_pos, derivative, last_err;
    long int i;
    
    bool reaching_pos;
public:
    Intake intake;
    
    Elevator(int elv_port, int elv_ch_a, int elv_ch_b, int arm_pivot_pot_port, int arm_pivot_enc_a, int arm_pivot_enc_b, int flipper_port, int rin_port, int lin_port);  // Use def directly?
    
    void SetPosition(int position);
    
    void UpdatePID();
    
    void Set(double rate);
    void SetForJoy(double rate);
};

#endif // ELEVATOR_H_
