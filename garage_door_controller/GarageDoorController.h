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
	void processInput(char input);
	GarageDoorController();
	virtual ~GarageDoorController();
	setInfraredActive(bool active);
	setOvercurrentActive(bool active);
private:
	void setState(State newState);
}

#endif /* GARAGEDOORCONTROLLER_H_ */
