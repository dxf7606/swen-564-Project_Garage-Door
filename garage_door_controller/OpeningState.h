/*
 * OpeningState.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "State.h"
#include "Motor.h"
#include "GarageDoorController.h"
 
#ifndef OPENINGSTATE_H_
#define OPENINGSTATE_H_

class OpeningState: public State {
public:
	OpeningState(Motor motor, GarageDoorController gdController);
	virtual ~OpeningState();
};

#endif /* OPENINGSTATE_H_ */
