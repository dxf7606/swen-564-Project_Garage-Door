/*
 * State.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include <stdio.h>
#include <stdlib.h>
#include "State.h"
#include "Motor.h"
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

namespace handler_space {
	uintptr_t d_i_o_control_handle;
    uintptr_t d_i_o_port_a_handle;
    uintptr_t d_i_o_port_b_handle;
}

void State::buttonInterrupt() {
	switch(this->curState){
		case ClosedState:
			buttonInterrupt_Closed();
			break;
		case OpeningState:
			buttonInterrupt_Opening_Closing();
			break;
		case OpenState:
			buttonInterrupt_Open();
			break;
		case ClosingState:
			buttonInterrupt_Opening_Closing();
			break;
		case InputInterruptState:
			switch(this->lastState) {
				case ClosingState:
					buttonInterrupt_Closed();
					break;
				case OpeningState:
					buttonInterrupt_Open();
					break;
				case ClosedState:
					buttonInterrupt_Closed();
					break;
				case OpenState:
					buttonInterrupt_Open();
					break;
				case InputInterruptState:
					buttonInterrupt_Closed();
					break;
			}
			break;
	}
}

void State::buttonInterrupt_Closed() {
	if (this->useKeyboard) {
		this->infraredActive=false;
		this->overcurrentActive=true;
		this->motor->setMotorDown(false);
		this->motor->setMotorUp(true);
	} else {
		out8(handler_space::d_i_o_port_a_handle, 0x01);
	}
	this->lastState = this->curState;
	this->curState = OpeningState;
	printf("Button input received\nInfrared set to inactive\nOvercurrent set to active\nMotor opening\n\n");
}

void State::OvercurrentInterrupt_Closing() {
	if (this->useKeyboard) {
		this->infraredActive=false;
		this->overcurrentActive=false;
		this->motor->setMotorDown(false);
		this->motor->setMotorUp(true);
	} else {
		out8(handler_space::d_i_o_port_a_handle, 0x01);
	}
	this->lastState = this->curState;
	this->curState = OpeningState;
	printf("Overcurrent input received\nInfrared set to inactive\nOvercurrent set to inactive\nMotor opening\n\n");
}

void State::OvercurrentInterrupt_Opening_Closing() {
	if (this->useKeyboard) {
		this->infraredActive=false;
		this->overcurrentActive=false;
		this->motor->setMotorUp(false);
		this->motor->setMotorDown(false);
	} else {
		out8(handler_space::d_i_o_port_a_handle, 0x00);
	}
	this->lastState = this->curState;
	this->curState = InputInterruptState;
	printf("Overcurrent input received\nInfrared set to inactive\nOvercurrent set to inactive\nMotor stopped\n\n");
}

void State::buttonInterrupt_Opening_Closing() {
	if (this->useKeyboard) {
		this->infraredActive=false;
		this->overcurrentActive=false;
		this->motor->setMotorUp(false);
		this->motor->setMotorDown(false);
	} else {
		out8(handler_space::d_i_o_port_a_handle, 0x00);
	}
	this->lastState = this->curState;
	this->curState = InputInterruptState;
	printf("Button input received\nInfrared set to inactive\nOvercurrent set to inactive\nMotor stopped\n\n");
}

void State::buttonInterrupt_Open() {
	if (this->useKeyboard) {
		this->infraredActive=true;
		this->overcurrentActive=true;
		this->motor->setMotorUp(false);
		this->motor->setMotorDown(true);
	} else {
		out8(hanlder_space::d_i_o_port_a_hanlde, 0x06);
	}
	this->lastState = this->curState;
	this->curState = ClosingState;
	printf("Button input received\nInfrared set to active\nOvercurrent set to active\nMotor closing\n\n");
}

void State::infraredInterrupt() {
	if (this->curState == ClosingState) {
		if (this->useKeyboard) {
			this->infraredActive=false;
			this->overcurrentActive=false;
			this->motor->setMotorDown(false);
			this->motor->setMotorUp(true);
		} else {
			out8(handler_space::d_i_o_port_a_handle, 0x01);
		}
		this->lastState = this->curState;
		this->curState = OpeningState;
		printf("Infrared input received\nInfrared set to inactive\nOvercurrent set to inactive\nMotor opening\n\n");
	} else {
		return;
	}
}

void State::overcurrentInterrupt() {
	switch(this->curState){
		case ClosedState:
			break;
		case OpeningState:
			OvercurrentInterrupt_Opening_Closing();
			break;
		case OpenState:
			break;
		case ClosingState:
			OvercurrentInterrupt_Closing();
			break;
		case InputInterruptState:
			break;
	}
}

void State::doorOpenInterrupt() {
	if (this->curState == OpeningState) {
		if (this->useKeyboard) {
			this->motor->setMotorUp(false);
			this->motor->setMotorDown(false);
			this->overcurrentActive=false;
			this->infraredActive=false;
		} else {
			out8(handler_space::d_i_o_port_a_handle, 0x00);
		}
		this->lastState = this->curState;
		this->curState = OpenState;
		printf("Door fully open\nInfrared set to inactive\nOvercurrent set to inactive\nMotor stopped\n\n");
	} else {
		return;
	}
}

void State::doorClosedInterrupt() {
	if (this->curState == ClosingState) {
		if (this->useKeyboard) {
			this->motor->setMotorUp(false);
			this->motor->setMotorDown(false);
			this->overcurrentActive=false;
			this->infraredActive=false;
		} else {
			out8(handler_space::d_i_o_port_a_handle, 0x00);
		}
		this->lastState = this->curState;
		this->curState = ClosedState;
		printf("Door fully closed\nInfrared set to inactive\nOvercurrent set to inactive\nMotor stopped\n\n");
	} else {
		return;
	}
}

State::State(Motor *m, bool useKeyboard) {
	this->motor = m;
	this->curState = ClosedState;
	this->lastState = ClosedState;
	this->useKeyboard = useKeyboard;
	if (!useKeyboard){
		out8(handler_space::d_i_o_port_a_handle, 0);
	}
}
