/*
 * MotorController.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "InputController.h"
#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

class MotorController: public InputController {
public:
	MotorController();
	virtual ~MotorController();
    void sendInput(char input);
};

#endif /* MOTORCONTROLLER_H_ */
