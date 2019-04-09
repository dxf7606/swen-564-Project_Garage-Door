/*
 * Motor.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

//#include <chrono>
#ifndef MOTOR_H_
#define MOTOR_H_

class Motor {
public:
    void setMotorUp(bool setting);
    void setMotorDown(bool setting);
	Motor(bool useKeyboard);
};

#endif /* MOTOR_H_ */
