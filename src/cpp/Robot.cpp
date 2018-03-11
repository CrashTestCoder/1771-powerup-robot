#include "WPILib.h"

#include <IterativeRobot.h>

/* Dashboard Libraries */
#include <SmartDashboard/SmartDashboard.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>

/* Our classes */
#include <Definitions.h>
#include <DriveTrain.h>
#include <Inputs.h>
#include <Elevator.h>
#include <AHRS.h>
#include <Point.h>


using namespace frc;

class Robot: public IterativeRobot {
private:
    frc::LiveWindow* lw = LiveWindow::GetInstance();
    frc::SendableChooser<std::string> chooser;
    DriveTrain driveTrain;
    Inputs in;
    Elevator elevator;
    Solenoid wings;
    AHRS *navx;
    frc::DigitalInput hall_effect_sensor;
    
    // Error correction due to diagonal electronics board
    double navrollinit, navpitchinit;
    
    bool naverr = 0;
    double lastdist = 0;
    double start_angle;
    
    // Point for auton
    Point currentPoint;
    
    int intake_val = 0;     // What's this for?
    
public:
    
    Robot() :   driveTrain(LTR_MOTOR_A, LTR_MOTOR_B, RTR_MOTOR_A, RTR_MOTOR_B, L_ENC_CHA, L_ENC_CHB, R_ENC_CHA, R_ENC_CHB, SHIFTER_PORT, PTO_PORT),
                in(JOY_LEFT, JOY_RIGHT, JOY_OTHER),
                elevator(ELEVATOR_MOTOR_PORT, ELEVATOR_ENC_CHA, ELEVATOR_ENC_CHB, ARM_PIVOT_PORT, ARM_PIVOT_ENC_A, ARM_PIVOT_ENC_B, FLIPPER_PORT, RIGHT_ARM_IN_PORT, LEFT_ARM_IN_PORT),
                wings(WINGS_PORT),
                hall_effect_sensor(0){
                    
                    try{
                        navx = new AHRS(SPI::Port::kMXP);
                    }catch(std::exception& e){
                        // Don't get an error please thank you
                        naverr = 1;     // you should probably use this somewhere
                    }
                    
                    navx->ZeroYaw();    // Ignores possible failure imediatly
                    
    }
    
    void RobotInit() {
        PutNumbers();
        wings.Set(1);
        navx->ZeroYaw();
        navrollinit = navx->GetRoll();
        navpitchinit = navx->GetPitch();
    }

    void DisabledInit() { }
    
    void AutonomousInit() {
        navx->ZeroYaw();
        start_angle = navx->GetAngle();
    }
    void TeleopInit() {
        navrollinit = navx->GetRoll();
        navpitchinit = navx->GetPitch();
        elevator.intake.SetFlipper(1);
    }
    
    void TestInit() { }

    void DisabledPeriodic() {
        PutNumbers();
    }
    void AutonomousPeriodic() {
//        Point p;
//        double avgds = driveTrain.GetAvgRaw() - lastdist;
//        p.Set(avgds*cos(navx->GetAngle()*PI/180.0), avgds*sin(navx->GetAngle()*PI/180.0));
//        currentPoint += p;
//        lastdist = driveTrain.GetAvgRaw();
        
        if(driveTrain.GetAvgRaw() < 7000){
            
            double left_mod = 1.0, right_mod = 1.0;
            
            if(navx->GetAngle() > start_angle + 1){
                left_mod = 1.7;
            } if(navx->GetAngle() < start_angle - 1){
                right_mod = 1.7;
            }
            
            driveTrain.Tank(0.6 * left_mod, 0.6 * right_mod);
            
            
        }
    }
    
    void TeleopPeriodic() {
        /* SPIN CODE
         * driveTrain.Tank(-1, -1);
         */
        
        PutNumbers();
//        if(in.GetLeftButton(CLIMB_BUTTON_A) && in.GetLeftButton(CLIMB_BUTTON_B)){
//            driveTrain.EnableClimb();
//        }
        
        if(!driveTrain.IsClimbing()){
//            if(navx->GetRoll()-navrollinit > FORWARD_TIP){                        // No, use derivitives and dont let the driver interfere until its fixed
//                driveTrain.Tank(1.5 * in.GetLeftY(), 1.5 * in.GetRightY());
//            }else if(navx->GetRoll()-navrollinit < BACKWARD_TIP){
//                driveTrain.Tank(-1.5 * in.GetLeftY(), -1.5 * in.GetRightY());
//            }else{ // Bot is not tipping
                driveTrain.Tank(in.GetLeftY(),in.GetRightY());
            //          }
            
            intake_val = 0;     // Y
            
            if(in.GetLeftButton(INTAKE_BUTTON_IN)){
                elevator.intake.SetPivotArm(INTAKE_IN_PT);
                elevator.intake.SetIntakeWheels(-INTAKE_WHEEL_SPEED);
            }else if(in.GetLeftButton(INTAKE_BUTTON_SHOOT)){
                if(elevator.intake.SetPivotArm(INTAKE_SHOOT_PT));
                    elevator.intake.SetIntakeWheels(INTAKE_WHEEL_SPEED);
            }else{
                elevator.intake.SetPivotArm(INTAKE_UP_PT);
                elevator.intake.SetIntakeWheels(-INTAKE_WHEEL_SPEED * 0.2);
            }
            
            if(in.GetLeftButton(MANUAL_SHIFT_BUTTON)){
                driveTrain.Shift(1);
            }else{
                driveTrain.Shift(0);
            }
            //driveTrain.AutoShift();
        }else{
            driveTrain.Tank(in.GetLeftY(), in.GetRightY());
            /** CLIMB SHIFTING MIGHT BREAK EVERYTHING BEWARE **/
            driveTrain.AutoShift();
        }
        
        
    }
    
    void TestPeriodic() { }
    
    void PutNumbers(){
        SmartDashboard::PutString("Climb Status: ", std::to_string(driveTrain.IsClimbing()));
        SmartDashboard::PutString("NavX Angle: ",std::to_string(navx->GetAngle()));
        SmartDashboard::PutString("NavX Pitch: ", std::to_string(navx->GetRoll()-navrollinit));
        SmartDashboard::PutString("NavX Pitch Raw: ", std::to_string(navx->GetRoll()));
        SmartDashboard::PutString("Anti-tip: ", std::to_string((navx->GetRoll()-navrollinit > FORWARD_TIP || navx->GetRoll()-navrollinit < BACKWARD_TIP)));
        SmartDashboard::PutString("NavX Error Status: ",std::to_string(naverr));
        SmartDashboard::PutString("Left Joystick Y: ", std::to_string(in.GetLeftY()));
        SmartDashboard::PutString("Right Joystick Y: ", std::to_string(in.GetRightY()));
        SmartDashboard::PutString("Other Joystick Y: ", std::to_string(in.GetOtherY()));
        SmartDashboard::PutString("X:", std::to_string(currentPoint.GetX()));
        SmartDashboard::PutString("Y:", std::to_string(currentPoint.GetY()));
        SmartDashboard::PutString("Hall Effect Status:", std::to_string(hall_effect_sensor.Get()));
        SmartDashboard::PutString("Intake Wheel Direction:", std::to_string(intake_val));
    }
};

START_ROBOT_CLASS(Robot)
