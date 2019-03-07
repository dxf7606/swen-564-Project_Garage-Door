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
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


Motor::Motor() {
    // create motor
    this->position = 0;
    this->motorUp = false;
    this->motorDown = false;
    this->refreshRate = 10000;
//    this->controller = c;
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void *threadWait(void *arg) {
	usleep(10000);
}

char Motor::closeDoor() {
//    while (true) {
//        if (getMotorDown() and getMotorUp()) {
//            // never supposed to happen, stop the thread (error state).
//            break;
//        }
//        else if (getPosition() <= 0 and getMotorDown()) {
//            // send fully closed input. Turn off motorDown
//            controller.sendInput('c');
//            motorDown = false;
//        }
//        else if (getPosition() >= 100 and getMotorUp()) {
//            // send fully open input. Turn off motorUp
//            controller.sendInput('o');
//            motorUp = false;
//        }
//        else if (getMotorDown()) {
//            position -= 1;
//        }
//        else if (motorUp) {
//            position += 1;
//        }
        
//        usleep(this->refreshRate);
//    }

	while (/*(this->motorDown==true && this->motorUp==false) && */this->position != 0 /*&& this->closing == true*/) {
		pthread_t motorThreadInst;
		pthread_create(&motorThreadInst, NULL, &threadWait, NULL);
		this->position--;
	}
	return 'c';
}

char Motor::openDoor() {
	while (this->position != 100) {
		pthread_t motorThreadInst;
		pthread_create(&motorThreadInst, NULL, &threadWait, NULL);
		this->position++;
	}
	return 'o';
}

char Motor::stopDoor() {
	//ToDo: Figure out how to actually interrupt closeDoor & openDoor
	return 'p';
}

void Motor::setMotorUp(bool setting) {
    this->motorUp = setting;
}

void Motor::setMotorDown(bool setting) {
    this->motorDown = setting;
}
