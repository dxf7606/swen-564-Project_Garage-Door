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
	Motor motor;
private:
	bool infraredActive;
	bool overcurrentActive;
    State *state;
	KeyboardController *keyboardController;
};

#endif /* GARAGEDOORCONTROLLER_H_ */
