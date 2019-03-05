/*
 * GarageDoorController.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */
#include <typeinfo>
#include <string>
#include <iostream>
#include "GarageDoorController.h"
#include "InputController.h"
#include "KeyboardController.h"
#include "Motor.h"
#include "State.h"
#include <pthread.h>
#include <stdio.h>
#include "inputBuffer.h"
#include <windows.h>
#include <unistd.h>

void *testPrint(void *arg) {
    while (true) {
        std::cout<<inputBuffer::inputBuffer[0];
        usleep(100000);
    }
}

namespace inputBuffer {
    char inputBuffer[1];
}

void GarageDoorController::processInput(char input) {
	switch (input) 
	{
		case 'm':
			break;
		case 'i':
			break;
		case 'r':
			break;
		case 'o':
			break;
		case 'c':
			break;
	}
}

void GarageDoorController::setInfraredActive(bool active) {
	this->infraredActive = active;
}

bool GarageDoorController::getInfraredActive() {
	return this->infraredActive;
}

void GarageDoorController::setOvercurrentActive(bool active) {
	this->overcurrentActive = active;
}

bool GarageDoorController::getOvercurrentActive() {
	return this->overcurrentActive;
}

GarageDoorController::GarageDoorController() {
	//this->lastState = new ClosingState();
	//this->curState = new ClosedState();
    InputController *c = new InputController();
    this->motor = new Motor(*c);
    this->keyboardController = new KeyboardController(*c);
	this->infraredActive = false;
	this->overcurrentActive = false;
}

GarageDoorController::~GarageDoorController() {
	// TODO Auto-generated destructor stub
}

int main() {
    GarageDoorController *g = new GarageDoorController();
    pthread_t doorControllerThread;
    pthread_create(&doorControllerThread, NULL, &testPrint, NULL);
    pthread_join(doorControllerThread, 0);
}
