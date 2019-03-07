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


namespace motorBuffer {
	bool motorUp;
	bool motorDown;
}

Motor::Motor() {

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void *threadWait(void *arg) {
	usleep(10000);
}

void *motorThread(void *arg) {
	int position = 0;
	bool motorUp = false;
	bool motorDown = false;
	int refreshRate = 10000;
    while (true) {
    	motorUp = motorBuffer::motorUp;
    	motorDown = motorBuffer::motorDown;
        if (motorDown and motorUp) {
            // never supposed to happen, stop the thread (error state).
            break;
        }
        else if (position <= 0 and motorDown) {
            // send fully closed input. Turn off motorDown
//            controller.sendInput('c');
            motorDown = false;
        }
        else if (position >= 100 and motorUp) {
            // send fully open input. Turn off motorUp
//            controller.sendInput('o');
            motorUp = false;
        }
        else if (motorDown) {
            position -= 1;
        }
        else if (motorUp) {
            position += 1;
        }
        
        usleep(refreshRate);
    }
}

void Motor::setMotorUp(bool setting) {
    motorBuffer::motorUp = setting;
}

void Motor::setMotorDown(bool setting) {
    motorBuffer::motorDown = setting;
}
