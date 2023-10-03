#include "QoSQueue.hpp"

// Creating a queue as requested
QueueHandle_t xQueueCreate(const size_t queueSize, const size_t elemSize, const char *name)
{
    if((queueSize < 2) || (elemSize < 1)) return NULL;
    QueueHandle_t ret = (QueueHandle_t)malloc(sizeof(Handler_t));         
    if (ret != NULL)
    {
        ret -> data = DS_Init(name, queueSize, elemSize);
        ret -> semHandle = sem_init(name, 1);                          // 1 = mutex
        ret -> elemSize = elemSize;
    }
    return ret;
}

// Checks if the queue is full
QoSQueueReturn_t xQueue_IsFull (QueueHandle_t queue)
{
    QoSQueueReturn_t ret = sem_wait(queue->semHandle);
    if(ret != 1) return QUEUE_ERROR;
    else
    {
        int temp = DS_Full(queue->data);

        ret = temp ? QUEUE_FULL : QUEUE_OK;     //  If the queue is full return QUEUE_FULL, otherwise QUEUE_OK      

    }
    sem_post(queue->semHandle);
    return ret;
}

// Checks if the queue is empty
QoSQueueReturn_t xQueue_IsEmpty (QueueHandle_t queue)
{
    QoSQueueReturn_t ret = sem_wait(queue->semHandle);
    if(ret != 1) return QUEUE_ERROR;        // Do we need to release the semaphore?
    else
    {
        int temp = DS_Empty(queue->data);

        ret = temp ? QUEUE_EMPTY : QUEUE_OK;     // If the queue is empty return QUEUE_EMPTY, otherwise QUEUE_OK    
    }
    sem_post(queue->semHandle);
    return ret;
}

// Inserts an element in the queue
QoSQueueReturn_t xQueue_Put (QueueHandle_t queue, const void *elem)
{
    if (queue == NULL) return QUEUE_ERROR;
    QoSQueueReturn_t ret = QUEUE_ERROR;
    if(xQueue_IsFull(queue) == QUEUE_FULL) return QUEUE_FULL;
    else
    {
        ret = sem_wait(queue->semHandle);
        if(ret != 1) return QUEUE_ERROR;
        else
        {
            void *dest = DS_GetHead(queue->data);
            memcpy(dest, elem, queue->elemSize);
        }
        sem_post(queue->semHandle);
    }
    return (QoSQueueReturn_t)ret;
}

// Extracts an element from the queue
QoSQueueReturn_t xQueue_Get (QueueHandle_t queue, void *elem)
{
    if (queue == NULL) return QUEUE_ERROR;
    QoSQueueReturn_t ret = QUEUE_ERROR;
    if(xQueue_IsEmpty(queue) == QUEUE_EMPTY) return QUEUE_EMPTY;
    else
    {
        ret = sem_wait(queue->semHandle);
        if(ret != 1) return QUEUE_ERROR;
        else
        {
            void *src = DS_GetTail(queue->data);
            memcpy(elem, src, queue->elemSize);
            ret = QUEUE_OK;
        }
        sem_post(queue->semHandle);
    }
    return (QoSQueueReturn_t)ret;
}

// Deletes the queue
QoSQueueReturn_t xQueue_Delete (QueueHandle_t queue)
{
    if (queue == NULL) return QUEUE_ERROR;
    void *sem = queue->semHandle;
    QoSQueueReturn_t ret = sem_wait(sem);

    DS_Delete(queue->data);
    free(queue);

    sem_post(sem);
    sem_destroy(sem);
    return (QoSQueueReturn_t)ret;
}

