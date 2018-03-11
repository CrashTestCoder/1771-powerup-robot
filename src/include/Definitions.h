#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define TBD                 1771

// TO-DO: CHANGE TBDs to actual values

#define PI                  3.1415926535897932384623383279

/*============= Button Mappings ==============*/
#define CLIMB_BUTTON_A      7
#define CLIMB_BUTTON_B      10
#define INTAKE_BUTTON_IN    3
#define INTAKE_BUTTON_SHOOT 4
#define INTAKE_BUTTON_FLIP  5
#define MANUAL_SHIFT_BUTTON 1

/*======== Ports and Encoder channels ========*/
#define JOY_LEFT            0
#define JOY_RIGHT           1
#define JOY_OTHER           2

/*================== Motors ==================*/
#define LTR_MOTOR_A         4
#define LTR_MOTOR_B         7
#define RTR_MOTOR_A         3
#define RTR_MOTOR_B         2
#define ELEVATOR_MOTOR_PORT TBD
#define RIGHT_ARM_IN_PORT   9
#define LEFT_ARM_IN_PORT    8
#define ARM_PIVOT_PORT      1

/*=== Encoders (and a single potentiometer) ===*/
#define L_ENC_CHA           TBD
#define L_ENC_CHB           TBD
#define R_ENC_CHA           TBD
#define R_ENC_CHB           TBD
#define ELEVATOR_ENC_CHA    TBD
#define ELEVATOR_ENC_CHB    TBD
#define ARM_PIVOT_ENC_A	    4
#define ARM_PIVOT_ENC_B     5

// Solenoids
#define SHIFTER_PORT        0
#define PTO_PORT            TBD
#define FLIPPER_PORT        1
#define WINGS_PORT          TBD

/*=== Speed constants and Encoder thresholds ===*/
#define CL_SPEED            TBD

#define SHIFT_UP_SPEED      2900
#define SHIFT_DOWN_SPEED    2200
#define CL_SHIFT_UP_SPEED   TBD
#define CL_SHIFT_DOWN_SPEED TBD
#define ELEVATOR_HIGH_PT    TBD
#define ELEVATOR_LOW_PT     TBD
#define INTAKE_WHEEL_SPEED  1
#define INTAKE_IN_PT        TBD
#define INTAKE_UP_PT        TBD
#define INTAKE_SHOOT_PT     TBD

#define ARM_PIVOT_SPEED     TBD

/*========== Coefficients for PID controllers ==========*/
#define ELEVATOR_P          TBD
#define ELEVATOR_I          TBD
#define ELEVATOR_D          TBD

/*========== Tipping Angle Constants ==========*/
#define FORWARD_TIP         18
#define BACKWARD_TIP        -18


#endif // DEFINITIONS_H_
