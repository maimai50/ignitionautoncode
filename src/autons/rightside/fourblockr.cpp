#include "lemlib/api.hpp"
#include "../../../include/configs.h"
#include "../autons.h"

void fourblockr() {
    chassis.setPose(0,-4.5,0);
    chassis.moveToPoint(16,25,500);
    chassis.waitUntil(13.7); 
    chassis.cancelMotion();
    chassis.turnToHeading(300,400);
    chassis.moveToPoint(20,14,300, {.forwards=false}); //tune this section

    chassis.swingToHeading(160, DriveSide::RIGHT, 1300, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE});
    chassis.waitUntil(200);
    chassis.resetLocalPosition();
    pros::delay(2000);
    chassis.swingToHeading(270, DriveSide::RIGHT, 380, {
        .minSpeed=50,
        .earlyExitRange=10
    });
    pros::delay(2000);
    chassis.turnToHeading(0,200,{.minSpeed=70,.earlyExitRange=10},true);
    chassis.swingToPoint(-10,-26, DriveSide::LEFT, 350, {
        .minSpeed=40,
        .earlyExitRange=7
    });
    chassis.moveToPoint(-9.5,-17,1000);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}