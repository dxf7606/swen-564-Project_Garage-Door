/*
 * State.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */
#include "Motor.h"
#ifndef STATE_H_
#define STATE_H_

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
	State(Motor *m);
private:
	void buttonInterrupt_Closed();
	void buttonInterrupt_Opening_Closing();
	void buttonInterrupt_Open();
	void buttonInterrupt_InputInterrupt();
	void OvercurrentInterrupt_Closing();
	void OvercurrentInterrupt_Opening_Closing();
    Motor *motor;
    Concrete_State curState;
    Concrete_State lastState;
    bool infraredActive;
    bool overcurrentActive;
};

#endif /* STATE_H_ */
