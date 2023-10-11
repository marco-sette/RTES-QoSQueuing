#include "Examples.hpp"

sem_t mutex, write_sem, read_sem;

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


// A function that writes elements on the queue
void *writer(void *arg)
{
    CircularQueue_t* queue = (CircularQueue_t*)arg;
    int i;
    for (i = 0; i < 10; i++)
    {
        int tmp = randomInt(0, 100);                // Generate a random integer
        DataStruct* data = newData(0, tmp);         // Create a new Data object
        xQueue_Put(queue, data);                    // Put the Data object on the bottom of the queue
        printf("Writer[%lu]: written %d on the queue.\n", pthread_self(), tmp);     // Print the value written
        pausetta(100, 500);                         // Pause for a random time
    }
    return NULL;
}

void *reader (void *arg)
{
    CircularQueue_t* queue = (CircularQueue_t*)arg;
    int i;
    for (i = 0; i < 10; i++)
    {
        DataStruct* data = (DataStruct*)xQueue_Get(queue);      // Get the Data object from the top of the queue
        if(data != NULL)
        {
            printf("Reader[%lu]: read %d from the queue.\n", pthread_self(), data->value);
            //printData(data);
            destroyData(data);
        }
        pausetta(100, 500);
    }
    return NULL;
}

void Queue_test(void)
{
    srand((unsigned int)time(NULL));
    pthread_t writers[N_WRITERS];
    pthread_t readers[N_READERS];

    sem_init(&mutex, 0, 1);
    sem_init(&write_sem, 0, 1);
    sem_init(&read_sem, 0, 1);


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

    sem_destroy(&mutex);
    sem_destroy(&write_sem);
    sem_destroy(&read_sem);

    xQueue_Delete(queue);

    printf("Queue test completed.\n");
}