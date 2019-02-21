/*
 * GarageDoorController.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "State.h"
#include "KeyboardController.h"
#include "Motor.h"
#include "InputController.h"

#ifndef GARAGEDOORCONTROLLER_H_
#define GARAGEDOORCONTROLLER_H_

class GarageDoorController {
public:
	void processInput(char input);
	GarageDoorController();
	virtual ~GarageDoorController();
	void setInfraredActive(bool active);
	bool getInfraredActive();
	bool getOvercurrentActive();
	void setOvercurrentActive(bool active);
private:
	bool infraredActive;
	bool overcurrentActive;
	State curState;
	State lastState;
	KeyboardController keyboardController;
	Motor motor;
	void setState(State newState);
};

#endif /* GARAGEDOORCONTROLLER_H_ */
