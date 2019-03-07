/*
 * State.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

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
	State();
	~State();
private:
	void buttonInterrupt_Closed(bool overcurrentActive);
	void buttonInterrupt_Opening_Closing();
	void buttonInterrupt_Open();
	void buttonInterrupt_InputInterrupt();
    Concrete_State curState;
    Concrete_State lastState;
};

#endif /* STATE_H_ */
