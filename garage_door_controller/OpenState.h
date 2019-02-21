/*
 * OpenState.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#ifndef OPENSTATE_H_
#define OPENSTATE_H_
#include "State.h"
#include "Motor.h"
#include "GarageDoorController.h"

class OpenState: public State {
public:
	OpenState(Motor motor, GarageDoorController gdController);
	virtual ~OpenState();
};

#endif /* OPENSTATE_H_ */
