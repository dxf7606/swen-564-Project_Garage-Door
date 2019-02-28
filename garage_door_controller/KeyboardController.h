/*
 * KeyboardController.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */
#include <unistd.h>
#include "InputController.h"
#ifndef KEYBOARDCONTROLLER_H_
#define KEYBOARDCONTROLLER_H_

class KeyboardController {
private:
    InputController controller;
    //void keyboardListener(void *arg);
public:
	KeyboardController(InputController controller);
	virtual ~KeyboardController();
};

#endif /* KEYBOARDCONTROLLER_H_ */
