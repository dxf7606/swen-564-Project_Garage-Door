/*
 * Motor.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 * 
 * Responsible for:
 * interpreting motor commands from state,
 * simulating movement,
 * generating open and closed signals
 */

#include "Motor.h"
#include "InputBuffer.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

namespace motorBuffer {
    bool motorUp = false;
    bool motorDown = false;
}

void *motorThread_Keyboard(void *arg) {
    int position = 0;
    bool motorUp = false;
    bool motorDown = false;
    int refreshRate = 100000;
    while (true) {
        motorUp = motorBuffer::motorUp;
        motorDown = motorBuffer::motorDown;
        if (motorDown and motorUp) {
            // never supposed to happen, stop the thread (error state).
            break;
        }
        else if (position <= 0 and motorDown) {
            // send fully closed input. Turn off motorDown

            inputBuffer::inputBuffer[0] = 'c';

            motorDown = false;
        }
        else if (position >= 100 and motorUp) {
            // send fully open input. Turn off motorUp

        	inputBuffer::inputBuffer[0] = 'o';

            motorUp = false;
        }
        else if (motorDown) {
            position -= 1;
            // send signal for motordown
        }
        else if (motorUp) {
            position += 1;
            // send signal for motorup
        }

        usleep(refreshRate);
    }
}

Motor::Motor(bool useKeyboard) {
    pthread_t mt;

    // ToDo: change the hard-coding of useKeyboard
    useKeyboard = false;

    if (useKeyboard) {
    	pthread_create(&mt, NULL, &motorThread_Keyboard, NULL);
    } else {
    	return;
    }
}

void Motor::setMotorUp(bool setting) {
    motorBuffer::motorUp = setting;
}

void Motor::setMotorDown(bool setting) {
    motorBuffer::motorDown = setting;
}
