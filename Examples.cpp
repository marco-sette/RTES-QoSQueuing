#include "Examples.hpp"

sem_t mutex, write_sem, read_sem;

int N_WRITERS = 15;
int N_READERS = 15;
int MAX_SIZE = 10;
int N_WRITER_ITERATIONS = 10;
int N_READER_ITERATIONS = 10;


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
    for (i = 0; i < N_WRITER_ITERATIONS; i++)
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
    for (i = 0; i < N_READER_ITERATIONS; i++)
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
    printf("\n");
}

void Queue_test2(int writers, int readers, int size, int writer_iterations, int reader_iterations)
{
    srand((unsigned int)time(NULL));
    pthread_t writers_t[writers];
    pthread_t readers_t[readers];

    sem_init(&mutex, 0, 1);
    sem_init(&write_sem, 0, 1);
    sem_init(&read_sem, 0, 1);

    CircularQueue_t* queue = xQueue_Init(size);

    N_WRITER_ITERATIONS = writer_iterations;
    N_READER_ITERATIONS = reader_iterations;

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

    sem_destroy(&mutex);
    sem_destroy(&write_sem);
    sem_destroy(&read_sem);

    xQueue_Delete(queue);

    printf("Queue test completed.\n");
    printf("\n");

}

void Queue_Manual(int writers, int readers, int size, int writer_iterations, int reader_iterations)
{
    
}

