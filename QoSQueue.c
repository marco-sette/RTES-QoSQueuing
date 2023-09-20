#include "QoSQueue.h"

QueueHandle_t xQueueCreate(const size_t queueSize, const size_t elemSize, const char *name)
{
    if((queueSize < 2) || (elemSize < 1)) return NULL;
    QueueHandle_t ret = (QueueHandle_t)malloc(sizeof(Handler_t));         // Malloc or emalloc???
    if (ret != NULL)
    {
        // PLACEHOLDER. Allocare la coda
        // PLACEHOLDER. Inizializzare i semafori
        ret->elemSize = elemSize;
    }
    return ret;
}

QoSQueueReturn_t xQueue_IsFull (QueueHandle_t queue)
{
    QoSQueueReturn_t ret = sem_wait(queue->semHandle);
    if(ret != 1) return QUEUE_ERROR;
    else
    {
        // PLACEHOLDER. Controllo se la coda è piena        
    }
    sem_post(queue->semHandle);
    return ret;
}

QoSQueueReturn_t xQueue_IsEmpty (QueueHandle_t queue)
{
    QoSQueueReturn_t ret = sem_wait(queue->semHandle);
    if(ret != 1) return QUEUE_ERROR;        // Va rilasciata la sezione critica?
    else
    {
        // PLACEHOLDER. Controllo se la coda è vuota        
    }
    sem_post(queue->semHandle);
    return ret;
}

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
            // PLACEHOLDER. Inserimento elemento in coda
        }
        sem_post(queue->semHandle);
    }
    return (QoSQueueReturn_t)ret;
}

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
            // PLACEHOLDER. Estrazione elemento dalla coda
        }
        sem_post(queue->semHandle);
    }
    return (QoSQueueReturn_t)ret;
}

QoSQueueReturn_t xQueue_Delete (QueueHandle_t queue)
{
    if (queue == NULL) return QUEUE_ERROR;
    // Salvo il riferimento al semaforo
    void *sem = queue->semHandle;
    QoSQueueReturn_t ret = sem_wait(sem);

    // PLACEHOLDER. Deallocazione coda
    // PLACEHOLDER. Free memory
    // PLACEHOLDER. Deallocazione semafori

    return (QoSQueueReturn_t)ret;
}

