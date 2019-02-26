/*
 * ClosingState.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 *      
 *      *will call Motor pauseGarage() method within buttonPush()*
 * 		*will call Motor pauseGarage() method followed by Motor setMotorUp() method within infraredInterrupt() and overcurrentInterrupt()*
 */

#include "ClosingState.h"
#include "GarageDoorController.h"

ClosingState::ClosingState(Motor motor, GarageDoorController gdController) {
	this->motor = motor;
	this->gdController = gdController;
}

ClosingState::~ClosingState() {
	// TODO Auto-generated destructor stub
}


