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

namespace motorBuffer {
    bool motorUp = false;
    bool motorDown = false;
}


void *motorThread(void *arg) {
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
        }
        else if (motorUp) {
            position += 1;
        }
        
        usleep(refreshRate);
    }
}

Motor::Motor() {
    pthread_t mt;
    pthread_create(&mt, NULL, &motorThread, NULL);
}

void Motor::setMotorUp(bool setting) {
    motorBuffer::motorUp = setting;
}

void Motor::setMotorDown(bool setting) {
    motorBuffer::motorDown = setting;
}
