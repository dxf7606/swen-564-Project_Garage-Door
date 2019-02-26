/*
 * GarageDoorController.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */
#include <typeinfo>
#include <string>
#include <iostream>
#include "GarageDoorController.h"
#include "InputController.h"
#include "KeyboardController.h"
#include "Motor.h"
#include "State.h"
#include "OpeningState.h"
#include "OpenState.h"
#include "ClosingState.h"
#include "ClosedState.h"
#include "InputInterruptState.h"

void GarageDoorController::processInput(char input) {
	switch (input) 
	{
		case 'm':
			this->setState(curState.overcurrentInterrupt());
			break;
		case 'i':
			this->setState(curState.infraredInterrupt());
			break;
		case 'r':
			this->setState(curState.buttonInterrupt());
			break;
		case 'o':
			this->setState(curState.doorOpenInterrupt());
			break;
		case 'c':
			this->setState(curState.doorClosedInterrupt());
			break;
	}
}

void GarageDoorController::setState(State newState) {
	if (typeid(this->curState).name() != typeid(newState).name()) {
		this->lastState = this->curState;
		this->curState = newState;
	}
}


void GarageDoorController::setInfraredActive(bool active) {
	this->infraredActive = active;
}

bool GarageDoorController::getInfraredActive() {
	return this->infraredActive;
}

void GarageDoorController::setOvercurrentActive(bool active) {
	this->overcurrentActive = active;
}

bool GarageDoorController::getOvercurrentActive() {
	return this->overcurrentActive;
}

GarageDoorController::GarageDoorController() {
	//this->lastState = new ClosingState();
	//this->curState = new ClosedState();
    InputController *c = new InputController();
    this->motor = new Motor(*c);
    this->keyboardController = new KeyboardController(*c);
	this->infraredActive = false;
	this->overcurrentActive = false;
}

GarageDoorController::~GarageDoorController() {
	// TODO Auto-generated destructor stub
}

int main() {
    GarageDoorController *g = new GarageDoorController();
}