/*
 * ClosingState.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 *      
 *      *will call Motor pauseGarage() method within buttonPush()*
 *		*will call Motor pauseGarage() method followed by Motor setMotorUp() method within infraredInterrupt() and overcurrentInterrupt()*
 */

#include "Motor.h"
#include "GarageDoorController.h"

#ifndef CLOSINGSTATE_H_
#define CLOSINGSTATE_H_

class ClosingState {
public:
	ClosingState(Motor motor, GarageDoorController gdController);
	virtual ~ClosingState();
};

#endif /* CLOSINGSTATE_H_ */
