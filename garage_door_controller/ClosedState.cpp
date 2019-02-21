/*
 * ClosedState.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 *      
 *      *Does not use/overwrite infraredInterrupt() or overcurrentInterrupt()*
 *		*will call Motor setMotorUp() method within buttonPush()*
 */
#include "Motor.h"
#include "ClosedState.h"
#include "GarageDoorController.h"
#include "OpeningState.h"

ClosedState::ClosedState(Motor eMotor, GarageDoorController egdController) :
	State(eMotor, egdController){}

ClosedState::~ClosedState() {
	// TODO Auto-generated destructor stub
}

OpeningState ClosedState::buttonPush() {
	this->gdController.setInfraredActive(false);
	this->gdController.setOvercurrentActive(true);
	this->motor.setMotorUp(true);
//	motorParam = *this->motor;
//	gdControllerParam = *this->gdController;
	return new OpeningState(this->motor, this->gdController);
}

