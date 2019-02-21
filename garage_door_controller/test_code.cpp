#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 5

void *worker_thread(void *arg) {
	//printf("This is worker_thread #%ld\n", (long)arg);
	//pthread_exit(NULL);
}
/*
int main(int argc, char *argv[]) {
	printf("Hellow World!");
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	pthread_t my_thread[N];

	long id;
	for(id = 1; id <= N; id++) {
	        int ret =  pthread_create(&my_thread[id], NULL, &worker_thread, (void*)id);
	        if(ret != 0) {
	                printf("Error: pthread_create() failed\n");
	                exit(EXIT_FAILURE);
	        }
	}

	pthread_exit(NULL);

	return EXIT_SUCCESS;
}
*/