#include "subsystems/classes.hpp"
#include "subsystems/systemconfig.hpp"
#include "api.h"
#include "config.h"
#include "main.h"
#include "pros/misc.h"

void driveControl() {
    chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
}

void intakeControl() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intakeInstance.in();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intakeInstance.out();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        intakeInstance.redirect(500);
    }
    else {
        intakeInstance.stop();
    }
}

void mogoControl() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        mogoInstance.clamp();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        mogoInstance.release();
    }
}

void liftControl() {
    liftInstance.updateState();
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        liftInstance.stow();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        liftInstance.alliance();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        liftInstance.wall();
    }
}


