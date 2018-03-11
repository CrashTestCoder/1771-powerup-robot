/* * * * * * * * * * * * * *
 *     Transmission.h      *
 * by Justin DeSimpliciis  *
 * * * * * * * * * * * * * */

#ifndef TRANSMISSION_H_
#define TRANSMISSION_H_

#include <WPILib.h>
#include <ctre/Phoenix.h>

class Transmission {
private:
    TalonSRX motor1, motor2;
    Encoder enc;
                    // Where's gear shift and pto
public:
    Transmission(int m1port, int m2port, int ech1, int ech2);
    
    /* Set rate for motors */
    void Set(double rate);
    
    /* Set neutral mode (duh) can be Coast or Brake */
    void SetNeutralMode(NeutralMode nm);
    
    /* Get motor current functions */
    double GetM1Current();
    double GetM2Current();
    double GetAvgCurrent();
    
    /* Encoder functions */
    void ResetEnc();
    double GetDistance();
    double GetRawEnc();
    double GetSpeed();
};


#endif // TRANSMISSION_H_
