#include "main.h"
#include "configs.h"
#include "lemlib/api.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::adi::DigitalOut matchloader('A');
pros::adi::DigitalOut descore('B'); //this also controlls outtake
pros::adi::DigitalOut placeholder ('C');
pros::adi::DigitalOut placeholder2 ('D');

pros::MotorGroup left_motors({1,2,3});
pros::MotorGroup right_motors({4,5,6});

pros::Imu inertial(7);
pros::Rotation verticalEnc(6);

lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, -0.75);

lemlib::Drivetrain drivetrain(
    &left_motors,
    &right_motors,
    13,
    lemlib::Omniwheel::OLD_325,
    450,
    2
);

lemlib::ControllerSettings linearPid(
    10, //kp
    0,  //ki
    5,  //kd
    0,  //anti windup
    0,  //small error range
    0,  //small error range timeout (ms)
    0,  //large error range
    0,  //large error range timeout (ms)
    0   //maximum acceleration (slew)
);

lemlib::ControllerSettings angularPid(
    10, //kp
    0,  //ki
    5,  //kd
    0,  //anti windup
    0,  //small error range
    0,  //small error range timeout (ms)
    0,  //large error range
    0,  //large error range timeout (ms)
    0   //maximum acceleration (slew)
);

lemlib::OdomSensors sensors(
    &vertical,
    nullptr,
    nullptr,
    nullptr,
    &inertial   
);

lemlib::ExpoDriveCurve throttleCurve(
    3,
    10,
    1.019
);

lemlib::ExpoDriveCurve steerCurve(
    3,
    10,
    1.019
);

lemlib::Chassis chassis(
    drivetrain,
    linearPid,
    angularPid,
    sensors,
    &throttleCurve,
    &steerCurve
);

