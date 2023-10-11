//#ifdef EXAMPLES_H
//#define EXAMPLES_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <unistd.h>

#include "QoSQueue.hpp"
#include "DataStr.hpp"

void shuffle(void *array[], size_t n);

#define N_WRITERS 15
#define N_READERS 20
#define MAX_SIZE 50


void* producer(void *arg);
void* consumer(void *arg);
void Queue_test(void);


//#endif // EXAMPLES_H