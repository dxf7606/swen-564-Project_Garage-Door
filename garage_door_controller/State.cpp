/*
 * State.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "State.h"
#include "Motor.h"
#include "GarageDoorController.h"

void State::buttonInterrupt() {
}

void State::buttonInterrupt_Closed() {
	
}

//void State::buttonInterrupt_Opening() {
//	this->gdController.setInfraredActive(false);
//	this->gdController.setOvercurrentActive(false);
//	this->motor.setMotorUp(false);
//	this->motor.setMotorDown(false);
//	this->lastState = this->curState;
//	this->curState = InputInterruptState;
//}

void State::infraredInterrupt() {
//	return this;
}

void State::overcurrentInterrupt() {
//	return this;
}

void State::doorOpenInterrupt() {
//	return this;

}

void State::doorClosedInterrupt() {
//	return this;

}

State::State() {
	//this->motor = eMotor;
	//this->gdController = egdController;
	this->lastState = ClosingState;
	this->curState = ClosedState;
}

State::~State() {
	// TODO Auto-generated destructor stub
}
