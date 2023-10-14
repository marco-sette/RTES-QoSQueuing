/*
** RTES-QoSQueuing: Examples.hpp - Examples for RTES-QoSQueuing
** ==========================================================================
** RTES-QoSQueuing - A simple RTES-QoSQueuing implementation for Linux
** ==========================================================================
** Authors: Francesco Sartor, Marco Francesco Sette
** Real-Time and Embedded Systems Project - University of Modena and Reggio Emilia
** Prof. Marko Bertogna and Prof. Paolo Burgio
** A.Y. 2022-2023
*/

//#ifdef EXAMPLES_H
//#define EXAMPLES_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <unistd.h>

#include "QoSQueue.hpp"
#include "DataStr.hpp"


void* writer(void *arg);
void* reader(void *arg);

void Queue_test(void);
void Queue_test2(int N_WRITERS, int N_READERS, int MAX_SIZE);


//#endif // EXAMPLES_H