#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <unistd.h>

#include "Examples.h"

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

// A function that returns a random number between lower and upper, used for pausing
static void pausetta (const unsigned int lower, const unsigned int upper)
{
    return((unsigned int)rand() % (upper - lower + 1)) + lower;
}
