/*
 * ClosedState.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "State.h"
#include "Motor.h"
#include "GarageDoorController.h"
#include "OpeningState.h"
 
#ifndef CLOSEDSTATE_H_
#define CLOSEDSTATE_H_

class ClosedState: public State {
public:
	ClosedState(Motor eMotor, GarageDoorController egdController);
	OpeningState buttonPush();
	virtual ~ClosedState();
};

#endif /* CLOSEDSTATE_H_ */
