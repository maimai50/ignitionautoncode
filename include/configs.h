#pragma once

#include "main.h"
#include "lemlib/api.hpp"
extern pros::Controller master;

//pneumatics
extern pros::adi::DigitalOut matchloader;
extern pros::adi::DigitalOut descore;
extern pros::adi::DigitalOut placeholder;
extern pros::adi::DigitalOut placeholder2;

//drive motors
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

//sensors
extern pros::Imu inertial;
extern pros::Rotation verticalEnc;

//lemobjects
extern lemlib::Chassis chassis;
extern lemlib::TrackingWheel vertical;

//pids
extern lemlib::ControllerSettings linearPid;
extern lemlib::ControllerSettings angularPid;