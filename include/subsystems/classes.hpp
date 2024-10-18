#pragma once
#include "api.h"
#include "lemlib/pid.hpp"

class Intake {

    public:
        Intake(pros::Motor intakeMotor); // pros::Optical opticalSensor
        void in();
        void out();
        // void redirect(int redirWait);
        void stop();
        void setSpeed(int speed);
        // int filterHue(float redLower, float redHigher, float blueLower, float blueHigher);

        private:
        pros::Motor intakeMotor;
        // pros::Optical opticalSensor;
        int intakeSpeed;
        int redirWait;
        float redLower;
        float redHigher;
        float blueLower;
        float blueHigher;
};

class Mogo {

    public:
        Mogo(pros::adi::Pneumatics mogoPiston);
        void clamp();
        void release();
        void toggle();

        private:
        pros::adi::Pneumatics mogoPiston;
};

class Lift {
    public:
        enum States {
            STOW,
            ALLIANCE,
            WALL,
            WALLSCORE
        };
        Lift(pros::Motor liftMotor1, pros::Motor liftMotor2, lemlib::PID liftPID, float stowPos, float alliancePos, float wallPos, float wallScore, float gearRatio);
        void stow();
        void alliance();
        void wall();
        void scorewall();
        void updateState();
        void setBrake(pros::motor_brake_mode_e brakeMode);
        

    private:
    float setPosition;
    float currentPosition;
    float error;
    lemlib::PID liftPID;
    float stowPos;
    float alliancePos;
    float wallPos;
    float wallScore;
    pros::Motor liftMotor1;
    pros::Motor liftMotor2;
    float gearRatio;
    States state;
};