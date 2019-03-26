/*
 * GarageDoorController.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mll8657
 */
#include "GarageDoorController.h"
#include "InputController.h"
#include "KeyboardController.h"
#include "Motor.h"
#include "State.h"
#include <pthread.h>
#include "inputBuffer.h"
#include <unistd.h>

GarageDoorController *g;

namespace inputBuffer {
    char inputBuffer[1];
}

void *garageDoorThread(void *arg) {
    while (true) {
        char input = inputBuffer::inputBuffer[0];
        inputBuffer::inputBuffer[0] = (char) 0;
         if (input != (char) 0) {
             g->processInput(input);
         }
        usleep(100000);
    }
}

void GarageDoorController::processInput(char input) {
    switch (input) 
    {
        case 'm':
            this->state->overcurrentInterrupt();
            break;
        case 'i':
            this->state->infraredInterrupt();
            break;
        case 'r':
            this->state->buttonInterrupt();
            break;
        case 'o':
            this->state->doorOpenInterrupt();
            break;
        case 'c':
            this->state->doorClosedInterrupt();
            break;
    }
}

GarageDoorController::GarageDoorController() {
    InputController *c = new InputController();
    Motor *m = new Motor();
    this->state = new State(m);
    this->keyboardController = new KeyboardController(*c);
}

int main() {
    g = new GarageDoorController();
    pthread_t doorControllerThread;
    pthread_create(&doorControllerThread, NULL, &garageDoorThread, NULL);
    pthread_join(doorControllerThread, 0);
}
