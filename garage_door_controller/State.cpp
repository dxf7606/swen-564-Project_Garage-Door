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
			buttonInterrupt_Closed();
			break;
		case OpeningState:
			this->gdController.setInfraredActive(false);
			this->gdController.setOvercurrentActive(false);
			this->motor.setMotorUp(false);
			this->motor.setMotorDown(false);
			this->lastState = this->curState;
			this->curState = InputInterruptState;
			break;
		case OpenState:
			this->gdController.setInfraredActive(true);
			this->gdController.setOvercurrentActive(true);
			this->motor.setMotorUp(false);
			this->motor.setMotorDown(true);
			this->lastState = this->curState;
			this->curState = ClosingState;
			break;
		case InputInterruptState:
			switch(this->lastState) {
				case ClosingState:
//					this->gdController.setInfraredActive(false);
//					this->gdController.setOvercurrentActive(true);
//					this->motor.setMotorDown(false);
//					this->motor.setMotorUp(true);
//					this->lastState = this->curState;
//					this->curState = OpeningState;
					buttonInterrupt_Closed();
					break;
				case OpeningState:
					this->gdController.setInfraredActive(true);
					this->gdController.setOvercurrentActive(true);
					this->motor.setMotorUp(false);
					this->motor.setMotorDown(true);
					this->lastState = this->curState;
					this->curState = ClosingState;
					break;
			}
			break;
	}
}

void State::buttonInterrupt_Closed() {
	this->gdController.setInfraredActive(false);
	this->gdController.setOvercurrentActive(true);
	this->motor.setMotorUp(true);
	this->lastState = this->curState;
	this->curState = OpeningState;
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

State::State(Motor eMotor, GarageDoorController egdController) {
	this->motor = eMotor;
	this->gdController = egdController;
	this->lastState = ClosingState;
	this->curState = ClosedState;
}

State::~State() {
	// TODO Auto-generated destructor stub
}
