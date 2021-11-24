//=========================================================
//CS 433 Assignment 4
//Your names: Jasmine Meyer & Birhane Diarra
//File type: main.cpp
//Purpose: Main driver to simulate the program. 
//Program that solves 'The Producer-Consumer Problem using the Pthreads API.
//===========================================================
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h>
#include "buffer.h"


// semaphores needed for syncronization
pthread_mutex_t mutex;	// mutex lock
sem_t full;				// counting sempahore
sem_t empty;			// counting semaphore
int sleeptime;
// forward declarations used in producer consumer functions
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void display();

// PURPOSE: produces an item in the buffer.
// PARAMETER: *param = used to pass pthread_create function
void* producer(void *param)
{
	buffer_item item;

	while (true) {
		sleep(rand() % 3);					// alternates between sleeping and producing
		item = rand() % 100;			// generate random number for item

		sem_wait(&empty);					// acquire the semaphore, wait till not full
		pthread_mutex_lock(&mutex);			// enforce the mutex to access critical section

		// critical section ...
		if (insert_item(item) == 0) {
			std::cout << "Item "<< item << " inserted by a producer.\n The current content of the buffer is ";
			display();
		}
		else {
			std::cout << "error: unable to produce";
		}
		// end of critical section ...

		pthread_mutex_unlock(&mutex);		// unlock the mutex
		sem_post(&full);					// release the semaphore, increment full
	}
}

// PURPOSE: consumes an item in the buffer.
// PARAMETER: *param = used to pass pthread_create function
void *consumer(void *param)
{
	buffer_item item;

	while (true) {
		sleep(rand() % 3);					// alternates between sleeping and consuming
		sem_wait(&full);					// acquire the semaphore, wait til not empty
		pthread_mutex_lock(&mutex); 		// enforce the mutex to access critical section

		// critical section ...
		if (remove_item(&item) == 0) {
			std::cout << "Item "<< item << " removed by a consumer.\n The current content of the buffer is "; 
			display();
		}
		else {
			std::cout << "error: unable to consume";
		}
		// end of critical section ...

		pthread_mutex_unlock(&mutex);		// unlock the mutex
		sem_post(&empty);					// release the semaphore, decrement empty
	}
}

// This is the driver to test out the implementation for solving the producer consumer problem.
int main(int argc, char *argv[])
{
  std::cout << "CS 433 Programming assignment 4\n"
	"Author: Birhane Diarra and Jasmine Meyer\n"
	"Date: 11/23/2021\n"
	"Course: CS433 (Operating Systems)\n"
	"Description: Program that solves 'The Producer-Consumer Problem', using the Pthreads API\n"
	"=================================" << std::endl;

	if (argc < 4 || argc > 4) {
		std::cout << "Usage: ./assign4 <sleeptime> <pthreadc> <cthreadc>" << std::endl;
		exit(1);
	}

	srand(time(NULL));


	// 1. Get command line arguments argv[1], argv[2], argv[3]
	int sleeptime = atoi(argv[1]);		// 1st arg is the sleep time
	int pthreadc = atoi(argv[2]);		// 2nd arg is the # of producer threads
	int cthreadc = atoi(argv[3]);		// 3rd arg is the # of consumer threads

	// 2. Initialize buffer / threads / semaphores
	pthread_t producer_threads[pthreadc];
	pthread_t consumer_threads[cthreadc];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, BUFFER_SIZE);	// empty initialized to buffer size
	sem_init(&full, 0, 0);				// full initialized to 0

	// 3. Create producer thread(s)
	for (int i = 0; i < pthreadc; i++)
		pthread_create(&producer_threads[i], NULL, producer, NULL);

	// 4. Create consumer thread(s)
	for (int i = 0; i < pthreadc; i++)
		pthread_create(&consumer_threads[i], NULL, consumer, NULL);

	// 5. Sleep 
	sleep(sleeptime);

	std::cout << "\nThreads finished! Exiting... \n";

	// 6. Exit 
	exit(0);
}