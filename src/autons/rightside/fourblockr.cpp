#include "lemlib/api.hpp"
#include "../../../include/configs.h"
#include "../autons.h"

void fourblockr() {
    chassis.moveToPoint(16,25,400);
    chassis.waitUntil(13.7); 
    chassis.cancelMotion();
    chassis.turnToHeading(270,450);
    chassis.moveToPoint(14,-15,400); //tune this section
    chassis.swingToHeading(160, DriveSide::LEFT, 1600);
    chassis.waitUntil(200);
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