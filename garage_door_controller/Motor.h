/*
 * Motor.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include <chrono>
#ifndef MOTOR_H_
#define MOTOR_H_

class Motor {
private:
    bool motorUp;
    bool motorDown;
    int position;
    void *motorThread(void *arg);
    std::chrono::milliseconds refreshRate;
public:
    void setMotorUp(bool setting);
    void setMotorDown(bool setting);
	Motor();
	virtual ~Motor();
};

#endif /* MOTOR_H_ */
