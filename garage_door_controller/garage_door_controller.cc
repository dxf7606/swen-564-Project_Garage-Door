#include <cstdlib>
#include <iostream>
#include <pthread.h>

void *input_thread(void *arg) {
	printf("This is worker_thread #%ld\n", (long)arg);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	//const pthread_t input_thread;

	//int ret =  pthread_create(&input_thread, NULL, &worker_thread, (void*)7);

	return EXIT_SUCCESS;
}
