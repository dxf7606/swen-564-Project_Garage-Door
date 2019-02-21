/*
 * GarageDoorController.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#ifndef GARAGEDOORCONTROLLER_H_
#define GARAGEDOORCONTROLLER_H_

class GarageDoorController {
public:
	void processInput(char);
	GarageDoorController();
	virtual ~GarageDoorController();
	setInfraredActive(bool);
	setOvercurrentActive(bool);
private:
	void setState(State);
}

#endif /* GARAGEDOORCONTROLLER_H_ */
