/*
 * State.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#ifndef STATE_H_
#define STATE_H_
#include "Motor.h"
#include "GarageDoorController.h"

enum Concrete_State {
	ClosedState,
	OpeningState,
	OpenState,
	ClosingState,
	InputInterruptState
};

class State {
public:
	void buttonInterrupt();
	void infraredInterrupt();
	void overcurrentInterrupt();
	void doorOpenInterrupt();
	void doorClosedInterrupt();
	State(Motor eMotor, GarageDoorController egdController);
	~State();
	Concrete_State curState;
	Concrete_State lastState;
	Motor motor;
	GarageDoorController gdController;
private:
	void buttonInterrupt_Closed(bool overcurrentActive);
	void buttonInterrupt_Opening_Closing();
	void buttonInterrupt_Open();
	void buttonInterrupt_InputInterrupt();
};

#endif /* STATE_H_ */
