/*
 * OpeningState.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "OpeningState.h"
#include "State.h"
#include "GarageDoorController.h"

OpeningState::OpeningState(Motor motor, GarageDoorController gdController):
	State(motor, gdController){}

OpeningState::~OpeningState() {
	// TODO Auto-generated destructor stub
}


