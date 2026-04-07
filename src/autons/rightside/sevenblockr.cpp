// seven block rush auton

#include "main.h"
#include "lemlib/api.hpp"
#include "../../../include/configs.h"
#include "../autons.h"

void sevenblockr(){
    chassis.setPose(0,0,0);
    chassis.moveToPoint(16,40,600);
    chassis.waitUntil(13.7);
    chassis.cancelMotion();
    chassis.moveToPose(27, 13, 180, 2000, {
        .forwards=false,
        .lead=0.5,
        .minSpeed=80,
        .earlyExitRange=5
    });
    chassis.moveToPoint(27, -4, 400);
    pros::delay(2000);
    chassis.moveToPoint(27,-9000,700);
    pros::delay(4000);
    chassis.resetLocalPosition();
    chassis.swingToHeading(270, DriveSide::RIGHT, 380, {
        .minSpeed=50,
        .earlyExitRange=10
    });
    chassis.turnToHeading(0,200,{.minSpeed=70,.earlyExitRange=10},true);
    chassis.swingToPoint(-10,-26, DriveSide::LEFT, 350, {
        .minSpeed=40,
        .earlyExitRange=7
    });
    chassis.moveToPoint(-9.5,-17,1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}