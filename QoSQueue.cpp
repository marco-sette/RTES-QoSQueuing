using namespace std;
#include <iostream>

#include "QoSQueue.hpp"

// Queue initialization
CircularQueue_t* xQueue_Init (const int capacity)
{
    CircularQueue_t* queue = (CircularQueue_t*)malloc(sizeof(CircularQueue_t));
    queue->buffer = (void**)malloc(capacity * sizeof(void*));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}


// Checks if the queue is full
int xQueue_IsFull (CircularQueue_t *queue)
{
    return ((queue->rear + 1) % queue->capacity == queue->front);
}

// Checks if the queue is empty
int xQueue_IsEmpty (CircularQueue_t *queue)
{
    return (queue->front == -1 && queue->rear == -1);
}

// Inserts an element in the queue
void xQueue_Put (CircularQueue_t *queue, void *data)
{
    if (xQueue_IsFull(queue)) 
    {
        std::cout << "Writer[" << pthread_self() << "]: \"Queue is full! Cannot add anymore.\"" << std::endl;
        return;
    }
    
    if(xQueue_IsEmpty(queue))
    {
        queue->front = queue->rear = 0;
    }
    else
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
    }
    queue->buffer[queue->rear] = data;
}

// Extracts an element from the queue
void* xQueue_Get (CircularQueue_t *queue)
{
    if (xQueue_IsEmpty(queue)) 
    {
        std::cout << "Reader[" << pthread_self() << "]: \"Queue is empty! Cannot extract.\"\n" << std::endl;
        return NULL;
    }
    
    void* data = queue->buffer[queue->front];
    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    return data;
}

// Deletes the queue
void xQueue_Delete (CircularQueue_t *queue)
{
    free(queue->buffer);
    free(queue);
}

