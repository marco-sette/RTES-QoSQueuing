#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <unistd.h>

#include "Examples.h"
#include "QoSQueue.h"

// A function that shuffles the elements of an array till n
void shuffle (void *array[], size_t n)
{
    srand((unsigned int)time(NULL));
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          void *t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

// A function that returns a random integer between lower and upper
static unsigned int randomInt (const unsigned int lower, const unsigned int upper)
{
    return((unsigned int)rand() % (upper - lower + 1)) + lower;
}

// A function that pauses for a random time between lower and upper
static void pausetta (const unsigned int lower, const unsigned int upper)
{
    unsigned int time = randomInt (lower, upper);
    usleep (time * 1000);
}

static QueueHandle_t QoSQueue;     // Queue handle
static sem_t sem;               // Semaphore

// A function that writes elements on the queue
void *writer(void *arg)
{
    int nb_writer = *(int *)arg;

    for(int i = 0; i < N_WRITES; i++)
    {
        Temp_t elem;
        elem.a = (double) randomInt (0, 100)/100;
        elem.b = elem.a * 2.0;
        snprintf (elem.name, 16, "Elemento[%d]", nb_writer + i);
        printf ("Writer [%d] : \"Writing on the buffer...\"\r\n", nb_writer);
        QoSQueueReturn_t retval = QoSQueue_Put (queue, &elem);

        switch(retval)
        {
        case QUEUE_OK:
            printf ("Writer [%d] : \"Written the element (%.2f, %.2f, %s) on the buffer!\"\r\n", nb_writer, elem.a, elem.b, elem.name);
            break;

        case QUEUE_FULL:
            printf ("Writer [%d] : \"The buffer is full! Cannot write the element on the buffer\"\r\n", nb_writer);
            break;

        default:
            printf ("Writer [%d] : \"Unknown error during Queue_Put()!\"\r\n", nb_writer);
            break;
        }
        pausetta (100, 500);
    }
    return NULL;
}

void *reader (void *arg)
{
    int nb_reader = *(int *)arg;

    int nb_cycles = N_WRITES;
    while ( (Queue_IsEmpty(queue) != True) || (nb_cycles > 0))
    {
        nb_cycles--;
        printf ("Reader [%d] : \"Reading from the buffer...\"\r\n", nb_reader);
        Temp_t elem;
        QoSQueueReturn_t retval = QoSQueue_Get (queue, &elem);
        
        switch(retval)
        {
            case QUEUE_OK:
                printf ("Reader [%d] : \"Read the element (%.2f, %.2f, %s) from the buffer!\"\r\n", nb_reader, elem.a, elem.b, elem.name);
                break;

            case QUEUE_EMPTY:
                printf ("Reader [%d] : \"The buffer is empty! Cannot read the element from the buffer\"\r\n", nb_reader);
                break;

            default:
                printf ("Reader [%d] : \"Unknown error during Queue_Get()!\"\r\n", nb_reader);
                break;
        }
        pausetta (100, 500);
    }
    return NULL;
}