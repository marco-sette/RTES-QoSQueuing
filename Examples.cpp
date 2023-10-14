/*
** RTES-QoSQueuing: Examples.cpp - Examples for RTES-QoSQueuing implementation
** ==========================================================================
** RTES-QoSQueuing - A simple RTES-QoSQueuing implementation for Linux
** ==========================================================================
** Authors: Francesco Sartor, Marco Francesco Sette
** Real-Time and Embedded Systems Project - University of Modena and Reggio Emilia
** Prof. Marko Bertogna and Prof. Paolo Burgio
** A.Y. 2022-2023
*/

using namespace std;
#include <iostream>

#include "Examples.hpp"

sem_t mutexw, mutexr, sempty, sfull;

int N_WRITERS = 15;
int N_READERS = 15;
int MAX_SIZE = 10;
int N_WRITES = 1;


// A function that returns a random integer between lower and upper
static unsigned int randomInt (const unsigned int lower, const unsigned int upper)
{
    return((unsigned int)rand() % (upper - lower + 1)) + lower;
}

// A function that pauses for a random time between lower and upper
static void timed_wait (const unsigned int lower, const unsigned int upper)
{
    unsigned int time = randomInt (lower, upper);
    usleep (time * 1000);
}


// A function that writes elements on the queue
void *writer(void *arg)
{
    CircularQueue_t* queue = (CircularQueue_t*)arg;
    int i=0, tmp;
    while(i<N_WRITES)
    {
        timed_wait(100, 500);                         // Pause for a random time (simulates an operation)

        // Generate a random message
        tmp = randomInt(0, 100);                // Generate a random integer
        DataStruct* data = newData(0, tmp);         // Create a new Data object

        sem_wait(&sempty);                               // Wait for an empty slot
        sem_wait(&mutexw);                               // Lock the queue

        // Write the message on the queue
        xQueue_Put(queue, data);                    // Put the Data object on the bottom of the queue
        std::cout << "Writer[" << pthread_self() << "]: \"Written " << tmp << " on the queue.\"" << std::endl;


        sem_post(&mutexw);                               // Unlock the queue
        sem_post(&sfull);                                // Signal that the queue is not empty

        i++;
    }
    pthread_exit(NULL);
}

void *reader (void *arg)
{
    CircularQueue_t* queue = (CircularQueue_t*)arg;
    int i = 0;
    while (i < N_WRITES * N_WRITERS / N_READERS)
    {
        timed_wait(100, 500);                         // Pause for a random time (simulates an operation)

        sem_wait(&sfull);                                // Wait for a full slot
        sem_wait(&mutexr);                               // Lock the queue

        // Read the message from the queue
        DataStruct* data = (DataStruct*)xQueue_Get(queue);      // Get the Data object from the top of the queue
        if(data != NULL)
        {
            std::cout << "Reader[" << pthread_self() << "]: \"Read "<< data->value <<" from the queue.\"" << std::endl;
            //printData(data);
            destroyData(data);
        }

        sem_post(&mutexr);                               // Unlock the queue
        sem_post(&sempty);                               // Signal that the queue is not full
        
        i++;
    }
    pthread_exit(NULL);
}

void Queue_test(void)
{
    srand((unsigned int)time(NULL));
    pthread_t writers[N_WRITERS];
    pthread_t readers[N_READERS];

    sem_init(&mutexw, 0, 1);
    sem_init(&mutexr, 0, 1);
    sem_init(&sempty, 0, MAX_SIZE);
    sem_init(&sfull, 0, 0);


    CircularQueue_t* queue = xQueue_Init(MAX_SIZE);

    int i;
    for( i = 0; i < N_WRITERS; i++)
    {
        pthread_create(&writers[i], NULL, writer, queue);
    }

    for( i = 0; i < N_READERS; i++)
    {
        pthread_create(&readers[i], NULL, reader, queue);
    }

    for( i = 0; i < N_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    for( i = 0; i < N_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    xQueue_Delete(queue);
    
    sem_destroy(&mutexw);
    sem_destroy(&mutexr);
    sem_destroy(&sempty);
    sem_destroy(&sfull);

    std::cout << "Queue test completed." << std::endl << std::endl;
}

void Queue_test2(int writers, int readers, int size)
{
    srand((unsigned int)time(NULL));
    pthread_t writers_t[writers];
    pthread_t readers_t[readers];

    sem_init(&mutexw, 0, 1);
    sem_init(&mutexr, 0, 1);
    sem_init(&sempty, 0, size);
    sem_init(&sfull, 0, 0);

    CircularQueue_t* queue = xQueue_Init(size);

    int i;
    for( i = 0; i < writers; i++)
    {
        pthread_create(&writers_t[i], NULL, writer, queue);
    }

    for( i = 0; i < readers; i++)
    {
        pthread_create(&readers_t[i], NULL, reader, queue);
    }

    for( i = 0; i < writers; i++)
    {
        pthread_join(writers_t[i], NULL);
    }

    for( i = 0; i < readers; i++)
    {
        pthread_join(readers_t[i], NULL);
    }

    xQueue_Delete(queue);

    sem_destroy(&mutexw);
    sem_destroy(&mutexr);
    sem_destroy(&sempty);
    sem_destroy(&sfull);

    std::cout << "Queue test completed."  << std::endl << std::endl;

}


