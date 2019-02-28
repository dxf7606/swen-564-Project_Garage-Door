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
	switch(this->curState){
		case ClosedState:
			buttonInterrupt_Closed(true);
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
					buttonInterrupt_Closed(true);
					break;
				case OpeningState:
					buttonInterrupt_Open();
					break;
				case ClosedState:
					buttonInterrupt_Closed(true);
					break;
				case OpenState:
					buttonInterrupt_Open();
					break;
				case InputInterruptState:
					buttonInterrupt_Closed(true);
					break;
			}
			break;
	}
}

void State::buttonInterrupt_Closed(bool overcurrentActive) {
//	this->gdController.setInfraredActive(false);
//	this->gdController.setOvercurrentActive(overcurrentActive);
//	this->motor.setMotorDown(false);
//	this->motor.setMotorUp(true);
	this->lastState = this->curState;
	this->curState = OpeningState;
}

void State::buttonInterrupt_Opening_Closing() {
//	this->gdController.setInfraredActive(false);
//	this->gdController.setOvercurrentActive(false);
//	this->motor.setMotorUp(false);
//	this->motor.setMotorDown(false);
	this->lastState = this->curState;
	this->curState = InputInterruptState;
}

void State::buttonInterrupt_Open() {
//	this->gdController.setInfraredActive(true);
//	this->gdController.setOvercurrentActive(true);
//	this->motor.setMotorUp(false);
//	this->motor.setMotorDown(true);
	this->lastState = this->curState;
	this->curState = ClosingState;
}

void State::infraredInterrupt() {
	if (this->curState == ClosingState) {
//		this->gdController.setInfraredActive(false);
//		this->gdController.setOvercurrentActive(false);
//		this->motor.setMotorDown(false);
//		this->motor.setMotorUp(true);
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
			buttonInterrupt_Closed(false);
			break;
		case InputInterruptState:
			break;
	}
}

void State::doorOpenInterrupt() {
	if (this->curState == OpeningState) {
//		this->motor.setMotorUp(false);
//		this->motor.setMotorDown(false);
//		this->gdController.setOvercurrentActive(false);
//		this->gdController.setInfraredActive(false);
		this->lastState = this->curState;
		this->curState = OpenState;
	} else {
		return;
	}
}

void State::doorClosedInterrupt() {
	if (this->curState == ClosingState) {
//		this->motor.setMotorDown(false);
//		this->motor.setMotorUp(false);
//		this->gdController.setOvercurrentActive(false);
//		this->gdController.setInfraredActive(false);
		this->lastState = this->curState;
		this->curState = ClosedState;
	} else {
		return;
	}
}

State::State(/*Motor eMotor, GarageDoorController egdController*/) {
//	this->motor = eMotor;
//	this->gdController = egdController;
	this->lastState = ClosingState;
	this->curState = ClosedState;
}

State::~State() {
	// TODO Auto-generated destructor stub
}
