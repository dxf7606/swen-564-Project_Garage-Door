/*
 * KeyboardController.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */

#include "KeyboardController.h"
#include "InputController.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "inputBuffer.h"

void *keyboardListener(void *arg) {
    char input;
    while (true) {
        std::cin>>input;
        inputBuffer::inputBuffer[0] = input;
        std::cout<<input;
    }
}

KeyboardController::KeyboardController(InputController controller) {
    this->controller = controller;
    pthread_t keyboardThread;
    pthread_create(&keyboardThread, NULL, &keyboardListener, NULL);
}

KeyboardController::~KeyboardController() {
	// TODO Auto-generated destructor stub
}

