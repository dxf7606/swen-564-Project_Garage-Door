/*
 * OpenState.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "OpenState.h"
#include "Motor.h"
#include "GarageDoorController.h"

OpenState::OpenState(Motor motor, GarageDoorController gdController) {
	this->motor = motor;
	this->gdController = gdController;
}

OpenState::~OpenState() {
	// TODO Auto-generated destructor stub
}
