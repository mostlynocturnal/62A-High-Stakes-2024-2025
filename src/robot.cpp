#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"

pros::MotorGroup right_motors({13, 17, 21}, pros::MotorGearset::blue);
pros::MotorGroup left_motors({-14, -15, -16}, pros::MotorGearset::blue);

pros::Motor intake(11, pros::MotorGearset::blue);

pros::Motor lift1(-18);
pros::Motor lift2(9);

pros::Imu imu(2);

pros::adi::Pneumatics mogo(2, false);

pros::Optical colorSensor(1);