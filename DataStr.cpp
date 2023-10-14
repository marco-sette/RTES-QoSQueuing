/*
** RTES-QoSQueuing: DataStr.cpp - Data structure for RTES-QoSQueuing, implementation
** ==========================================================================
** RTES-QoSQueuing - A simple RTES-QoSQueuing implementation for Linux
** ==========================================================================
** Authors: Francesco Sartor, Marco Francesco Sette
** Real-Time and Embedded Systems Project - University of Modena and Reggio Emilia
** Prof. Marko Bertogna and Prof. Paolo Burgio
** A.Y. 2022-2023
*/

using namespace std;
#include <iostream>

#include "DataStr.hpp"

// Function to create a new Data object
DataStruct* newData(int type, int value)
{
    DataStruct* data = (DataStruct*)malloc(sizeof(DataStruct));
    data->type = type;
    // Add specific data fields here
    data->value = value;
    return data;
}

// Function to destroy a Data object
void destroyData(DataStruct* data)
{
    free(data);
}

// Function to print a Data object
void printData(DataStruct* data)
{
    std::cout << "Data: " << data->type << "." << std::endl;
    // Add specific data fields here
    // For example, printf("Data: %d\n", data->value);
}



