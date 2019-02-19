/*
 * State.h
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#ifndef STATE_H_
#define STATE_H_

class State {
public:
	virtual State buttonInterrupt();
	virtual State infraredInterrupt();
	virtual State overcurrentInterrupt();
	virtual State doorOpenInterrupt();
	virtual State doorClosedInterrupt();
	State();
	virtual ~State();
};

#endif /* STATE_H_ */
