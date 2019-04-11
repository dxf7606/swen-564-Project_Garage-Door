/*
 * GarageDoorController.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */
#include "GarageDoorController.h"
#include "InputController.h"
#include "KeyboardController.h"
#include "Motor.h"
#include "State.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "inputBuffer.h"
#include <unistd.h>
#include <handler_space.h>
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

GarageDoorController *g;

namespace inputBuffer {
    char inputBuffer[1];
}

void *garageDoorThread(void *arg) {
    while (true) {
        char input = inputBuffer::inputBuffer[0];
        inputBuffer::inputBuffer[0] = (char) 0;
         if (input != (char) 0) {
             g->processInput(input);
         }
        usleep(100000);
    }
}

void GarageDoorController::processInput(char input) {
    switch (input) 
    {
        case 'm':
            this->state->overcurrentInterrupt();
            break;
        case 'i':
            this->state->infraredInterrupt();
            break;
        case 'r':
            this->state->buttonInterrupt();
            break;
        case 'o':
            this->state->doorOpenInterrupt();
            break;
        case 'c':
            this->state->doorClosedInterrupt();
            break;
    }
}

GarageDoorController::GarageDoorController() {
    InputController *c = new InputController();
    Motor *m = new Motor(false);
    this->state = new State(m);
    this->keyboardController = new KeyboardController(*c);
}

int GetRootAccess()
{
	int status = 0 ;
	int privity_err ;

	/* Give this thread root permissions to access the hardware */
	privity_err = ThreadCtl( _NTO_TCTL_IO, NULL );
	if ( privity_err == -1 )
	{
		printf("\nCan't get root permissions");
		fprintf( stderr, "can't get root permissions\n" );
		status = -1;
	}

	return status ;
}

int main() {
	if ( ! GetRootAccess() )
	{
		handler_space::d_i_o_control_handle = mmap_device_io( D_I_O_PORT_LENGTH, D_I_O_CONTROL_REGISTER ) ;
		handler_space::d_i_o_port_a_handle = mmap_device_io( D_I_O_PORT_LENGTH, D_I_O_PORT_A ) ;
		handler_space::d_i_o_port_b_handle = mmap_device_io( D_I_O_PORT_LENGTH, D_I_O_PORT_B ) ;
		out8( handler_space::d_i_o_control_handle, 0x02);
		g = new GarageDoorController();
	    pthread_t doorControllerThread;
	    pthread_create(&doorControllerThread, NULL, &garageDoorThread, NULL);
	    pthread_join(doorControllerThread, 0);
	}
	else
		printf( "\nFailure getting root access for I/O register mapping\n") ;

	return EXIT_SUCCESS;
}
