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


void* writer(void *arg);
void* reader(void *arg);

void Queue_test(void);
void Queue_test2(int N_WRITERS, int N_READERS, int MAX_SIZE, int N_WRITER_ITERATIONS, int N_READER_ITERATIONS);


//#endif // EXAMPLES_H