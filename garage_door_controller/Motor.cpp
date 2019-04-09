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
#include <inttypes.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/trace.h>		// to support TraceEvent calls
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/mman.h>     /* for mmap_device_io() */
#include <termios.h>
#include <handler_space.h>

#define D_I_O_PORT_LENGTH (1)
#define A_D_BASE_ADDRESS 0x280
#define D_I_O_CONTROL_REGISTER (A_D_BASE_ADDRESS + 0x0b)
#define D_I_O_PORT_A (A_D_BASE_ADDRESS + 0x08)
#define D_I_O_PORT_B (A_D_BASE_ADDRESS + 0x09)

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

void *motorThread_Simulator(void *arg) {
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
	out8( d_i_o_control_handle, 0x02) ;

    pthread_t mt;

    // ToDo: change the hard-coding of useKeyboard
    useKeyboard = false;

    if (useKeyboard) {
    	pthread_create(&mt, NULL, &motorThread_Keyboard, NULL);
    } else {
    	pthread_create(&mt, NULL, &motorThread_Simulator, NULL);
    }
}

void Motor::setMotorUp(bool setting) {
    motorBuffer::motorUp = setting;
}

void Motor::setMotorDown(bool setting) {
    motorBuffer::motorDown = setting;
}
