/*
 * Motor.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

//#include <chrono>
#include "InputController.h"
#ifndef MOTOR_H_
#define MOTOR_H_

class Motor {
public:
    void setMotorUp(bool setting);
    void setMotorDown(bool setting);
	Motor();
	virtual ~Motor();
};

#endif /* MOTOR_H_ */
