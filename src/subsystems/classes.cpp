#include "subsystems/classes.hpp"

Intake::Intake(pros::Motor& intakeMotor_, pros::Optical& opticalSensor)
    : intakeMotor(intakeMotor_), opticalSensor(opticalSensor) {
    this->redLower = 0;
    this->redHigher = 30;

    this->blueLower = 180;
    this->blueHigher = 210;
    }

void Intake::in() {
    intakeMotor.move_velocity(600);
}

void Intake::out() {
    intakeMotor.move_velocity(-600);
}

void Intake::redirect(int redirWait) {
    Intake::in();
    int hue = filterHue(redLower, redHigher, blueLower, blueHigher);
    if (hue != 0) {
        pros::delay(redirWait);
        Intake::out();
        pros::delay(500);
    }
}

void Intake::stop() {
    intakeMotor.move_velocity(0);
}

void Intake::setSpeed(int speed) {
    this->intakeSpeed = speed;
}

int Intake::filterHue(float redLower, float redHigher, float blueLower, float blueHigher) {
    float hue = opticalSensor.get_hue();
    if (hue > redLower && hue < redHigher) {
        return 1;
    }
    else if (hue > blueLower && hue < blueHigher) {
        return 2;
    }
    else {
        return 0;
    }
}

Mogo::Mogo(pros::adi::Pneumatics& mogoPiston_)
    : mogoPiston(mogoPiston_) {}

void Mogo::clamp() {
    mogoPiston.extend();
}

void Mogo::release() {
    mogoPiston.retract();
}

void Mogo::toggle() {
    mogoPiston.toggle();
}


Lift::Lift(pros::Motor& liftMotor1, pros::Motor& liftMotor2, lemlib::PID liftPID, float stowPos, float alliancePos, float wallPos, float wallScore, float gearRatio)
    : liftMotor1(liftMotor1), liftMotor2(liftMotor2), liftPID(liftPID), stowPos(stowPos), alliancePos(alliancePos), wallPos(wallPos), wallScore(wallScore), gearRatio(gearRatio), state(STOW) {}

void Lift::stow() {
    state = STOW;
}

void Lift::alliance() {
    state = ALLIANCE;
}

void Lift::wall() {
    if (state != WALL) {
        state = WALL;
    }
    else {
        state = WALLSCORE;
    }
} 

void Lift::scorewall() {
    state = WALLSCORE;
}

void Lift::updateState() {
    switch (state) {
        case STOW:
            this->setPosition = stowPos;
            break;
        case ALLIANCE:
            this->setPosition = alliancePos;
            break;
        case WALL:
            this->setPosition = wallPos;
            break;
        case WALLSCORE:
            this->setPosition = wallScore;
            break;
    };
    this->currentPosition = (liftMotor1.get_position() * gearRatio);
    this->error = setPosition - currentPosition;
    liftMotor1.move(liftPID.update(error));
    liftMotor2.move(liftPID.update(error));
}