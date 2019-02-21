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


Motor::Motor() {
    // create motor
    this->position = 0;
    this->motorUp = false;
    this->motorDown = false;
    this->refreshRate = 10;
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void *Motor::motorThread(void *arg) {
    while (true) {
        //std::this_thread::sleep_for(this->refreshRate);
    }
}

void Motor::setMotorUp(bool setting) {
    this->motorUp = setting;
}

void Motor::setMotorDown(bool setting) {
    this->motorDown = setting;
}
