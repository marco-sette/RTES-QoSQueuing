/*
** RTES-QoSQueuing: QoSQueue.hpp - Queue for RTES-QoSQueuing, Circular Buffer
** ==========================================================================
** RTES-QoSQueuing - A simple RTES-QoSQueuing implementation for Linux
** ==========================================================================
** Authors: Francesco Sartor, Marco Francesco Sette
** Real-Time and Embedded Systems Project - University of Modena and Reggio Emilia
** Prof. Marko Bertogna and Prof. Paolo Burgio
** A.Y. 2022-2023
*/

#ifndef QOSQUEUE_H_
#define QOSQUEUE_H_

#include <stdint.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include "QoSAccess.hpp"

typedef struct
{
    void** buffer;
    int capacity;
    int front;
    int rear;
} CircularQueue_t;

// Queue initialization
CircularQueue_t* xQueue_Init(const int capacity);

// Check if the queue is full
int xQueue_IsFull(CircularQueue_t *queue);

// Check if the queue is empty
int xQueue_IsEmpty(CircularQueue_t *queue);

// Put an element in the queue
void xQueue_Put(CircularQueue_t *queue, void *data);
   
// Get an element from the queue
void* xQueue_Get(CircularQueue_t *queue);

// Delete the queue
void xQueue_Delete(CircularQueue_t *queue);


#endif /* QOSQUEUE_H_ */
