/*
 * Motor.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 * 
 * Responsible for:
 * interpreting motor commands from controller,
 * simulating movement,
 * generating open and closed signals
 */

#include "Motor.h"
#include <cstdlib>
#include <stdlib.h>
#include <chrono>
#include <thread>


Motor::Motor() {
    // create motor
    this->position = 0;
    this->motorUp = false;
    this->motorDown = false;
    this->refreshRate = std::chrono::milliseconds(10);
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void *Motor::motorThread(void *arg) {
    while (true) {
        if (position <= 0 and motorDown) {
            // send fully closed input. Turn off motorDown
            motorDown = false;
        }
        
        if (position >= 100 and motorUp) {
            // send fully open input. Turn off motorUp
            motorUp = false;
        }
        
        if (motorDown and motorUp) {
            break;
        }
        
        std::this_thread::sleep_for(this->refreshRate);
    }
}

void Motor::setMotorUp(bool setting) {
    this->motorUp = setting;
}

void Motor::setMotorDown(bool setting) {
    this->motorDown = setting;
}
