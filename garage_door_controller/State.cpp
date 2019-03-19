/*
 * State.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "State.h"
#include "Motor.h"

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
	this->infraredActive=false;
	this->overcurrentActive=true;
	printf("Button input received\nInfrared set to inactive\nOvercurrent set to active\n");
	this->motor->setMotorDown(false);
	this->motor->setMotorUp(true);
	this->lastState = this->curState;
	this->curState = OpeningState;
}

void State::OvercurrentInterrupt_Closing() {
	this->infraredActive=false;
	this->overcurrentActive=overcurrentActive;
	printf("Button input received\nInfrared set to inactive\nOvercurrent set to inactive");
	this->motor->setMotorDown(false);
	this->motor->setMotorUp(true);
	this->lastState = this->curState;
	this->curState = OpeningState;
}

void State::buttonInterrupt_Opening_Closing() {
	this->infraredActive=false;
	this->overcurrentActive=false;
	this->motor->setMotorUp(false);
	this->motor->setMotorDown(false);
	this->lastState = this->curState;
	this->curState = InputInterruptState;
}

void State::buttonInterrupt_Open() {
	this->infraredActive=true;
	this->overcurrentActive=true;
	this->motor->setMotorUp(false);
	this->motor->setMotorDown(true);
	this->lastState = this->curState;
	this->curState = ClosingState;
}

void State::infraredInterrupt() {
	if (this->curState == ClosingState) {
		this->infraredActive=false;
		this->overcurrentActive=false;
		this->motor->setMotorDown(false);
		this->motor->setMotorUp(true);
		this->lastState = this->curState;
		this->curState = OpeningState;
	} else {
		return;
	}
}

void State::overcurrentInterrupt() {
	switch(this->curState){
		case ClosedState:
			break;
		case OpeningState:
			buttonInterrupt_Opening_Closing();
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
		this->motor->setMotorUp(false);
		this->motor->setMotorDown(false);
		this->overcurrentActive=false;
		this->infraredActive=false;
		this->lastState = this->curState;
		this->curState = OpenState;
	} else {
		return;
	}
}

void State::doorClosedInterrupt() {
	if (this->curState == ClosingState) {
		this->motor->setMotorDown(false);
		this->motor->setMotorUp(false);
		this->overcurrentActive=false;
		this->infraredActive=false;
		this->lastState = this->curState;
		this->curState = ClosedState;
	} else {
		return;
	}
}

State::State(Motor *m) {
    this->motor = m;
    this->curState = ClosedState;
    this->lastState = ClosedState;
    this->motor = motor;
}

State::~State() {
	// TODO Auto-generated destructor stub
}
