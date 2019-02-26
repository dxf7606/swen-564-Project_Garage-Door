/*
 * State.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "State.h"
#include "Motor.h"
#include "GarageDoorController.h"

State State::buttonInterrupt() {
	return this;

}

State infraredInterrupt() {
	return this;
}

State overcurrentInterrupt() {
	return this;
}

State State::doorOpenInterrupt() {
	return this;

}

State State::doorClosedInterrupt() {
	return this;

}

State::State(Motor eMotor, GarageDoorController egdController) {
	this->motor = eMotor;
	this->gdController = egdController;
}

State::~State() {
	// TODO Auto-generated destructor stub
}
