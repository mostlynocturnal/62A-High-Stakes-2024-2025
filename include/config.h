#pragma once
#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/misc.h"
#include "subsystems/classes.hpp"

inline pros::Controller master(pros::E_CONTROLLER_MASTER);
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
extern pros::Motor intake;
extern pros::MotorGroup lift;
extern pros::Motor lift1;
extern pros::Motor lift2;
extern pros::adi::Pneumatics mogo;
extern pros::Optical colorSensor;

extern pros::Imu imu;

inline lemlib::PID liftPID(3, 0, 2);

inline Lift liftInstance(lift1, lift2, liftPID, 0, 100, 210, 150, (12.0/60.0));

// inline float redlow = 0;
// inline float redhigh = 30;


// inline float bluelow = 180;
// inline float bluehigh = 210;

inline double trackWidth = 13;
inline int WheelSize = lemlib::Omniwheel::NEW_325;
inline int rpm = 450;
inline int HorzDrift = 8;

inline lemlib::Drivetrain drivetrain(&left_motors, &right_motors, trackWidth, WheelSize, rpm, HorzDrift);

inline lemlib::OdomSensors odom(nullptr,
                                nullptr, 
                                nullptr, 
                                nullptr, 
                                &imu);

inline Intake intakeInstance(intake, colorSensor);

inline Mogo mogoInstance(mogo);

inline lemlib::ControllerSettings lateral_controller(6, 0, 3, 3, 1, 100, 3, 500, 10);
inline lemlib::ControllerSettings angular_controller(6, 0, 3, 3, 1, 100, 3, 500, 10);

inline lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, odom);