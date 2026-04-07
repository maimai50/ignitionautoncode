#include "main.h"
#include "configs.h"
#include "lemlib/api.hpp"
#include "pros/motor_group.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::adi::DigitalOut matchloader('A');
pros::adi::DigitalOut descore('B'); //this also controlls outtake
pros::adi::DigitalOut placeholder ('C');
pros::adi::DigitalOut placeholder2 ('D');

pros::MotorGroup left_motors({16,-17,-18});
pros::MotorGroup right_motors({-8,9,10});

pros::Imu inertial(21);
pros::Rotation verticalEnc(20);

pros::MotorGroup intake({1,-2});

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
    12, //kp
    0,  //ki
    6,  //kd
    0,  //anti windup
    0,  //small error range
    0,  //small error range timeout (ms)
    0,  //large error range
    0,  //large error range timeout (ms)
    0   //maximum acceleration (slew)
);

lemlib::ControllerSettings angularPid(
    10, //kp
    0.03,  //ki
    60,  //kd
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

