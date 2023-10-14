/*
** RTES-QoSQueuing: DataStr.hpp - Data structure for RTES-QoSQueuing
** ==========================================================================
** RTES-QoSQueuing - A simple RTES-QoSQueuing implementation for Linux
** ==========================================================================
** Authors: Francesco Sartor, Marco Francesco Sette
** Real-Time and Embedded Systems Project - University of Modena and Reggio Emilia
** Prof. Marko Bertogna and Prof. Paolo Burgio
** A.Y. 2022-2023
*/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

typedef struct
{
    int type;       // Field to identify the type of the message
    // Add specific data fields here
    // For example, int value for an integer message
    int value;
    // char* value for a string message
} DataStruct;

// Function to create a new Data object
DataStruct* newData(int type, int value);

// Function to destroy a Data object
void destroyData(DataStruct* data);

#endif // DATA_STRUCT_HPP

// Function to print a Data object
void printData(DataStruct* data);
