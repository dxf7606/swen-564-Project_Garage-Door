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

static class GarageDoorController {
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
	KeyboardController *keyboardController;
	Motor *motor;
};

#endif /* GARAGEDOORCONTROLLER_H_ */
