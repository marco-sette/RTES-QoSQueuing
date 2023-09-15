#ifndef QOSQUEUE_H_
#define QOSQUEUE_H_

#include <stdint.h>
#include <stddef.h>

// Here we define all the return values of the functions
typedef enum
{
    QUEUE_OK = 0,
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_ERROR = -1,
} QoSQueueReturn_t;

// Struct used to handle the queue
typedef struct
{
    void *data;
    Queue_sem_t semHandle;
    size_t elemSize;
} Handler_t;

// New handler 
typedef Handler_t *QueueHandle_t;

// Create a new queue, given the size of the queue, a name and the size of the elements
QueueHandle_t xQueueCreate(const size_t queueSize, const size_t elemSize, const char *name);

// Check if the queue is full
QoSQueueReturn_t xQueue_IsFull(QueueHandle_t queue);

// Check if the queue is empty
QoSQueueReturn_t xQueue_IsEmpty(QueueHandle_t queue);

// Put an element in the queue
QoSQueueReturn_t xQueue_Put(QueueHandle_t queue, const void *ptrElem);

// Get an element from the queue
QoSQueueReturn_t xQueue_Get(QueueHandle_t queue, void *ptrDest);

// Delete the queue
QoSQueueReturn_t xQueue_Delete(QueueHandle_t queue);

#endif /* QOSQUEUE_H_ */
