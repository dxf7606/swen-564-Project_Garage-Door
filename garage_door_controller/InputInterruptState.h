/*
 * InputInterruptState.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */
#include "State.h"
#include "Motor.h"

#ifndef INPUTINTERRUPTSTATE_H_
#define INPUTINTERRUPTSTATE_H_

class InputInterruptState: public State {
public:
	InputInterruptState();
	virtual ~InputInterruptState();
};

#endif /* INPUTINTERRUPTSTATE_H_ */
