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
#include "InputController.h"
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
    this->controller = new InputController();
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void *Motor::motorThread(void *arg) {
    while (true) {
        if (motorDown and motorUp) {
            // never supposed to happen, stop the thread (error state).
            break;
        }
        else if (position <= 0 and motorDown) {
            // send fully closed input. Turn off motorDown
            controller->sendInput('c');
            motorDown = false;
        }
        else if (position >= 100 and motorUp) {
            // send fully open input. Turn off motorUp
            controller->sendInput('o');
            motorUp = false;
        }
        else if (motorDown) {
            position -= 1;
        }
        else if (motorUp) {
            position += 1;
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
