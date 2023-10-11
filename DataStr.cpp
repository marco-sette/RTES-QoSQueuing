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
    printf("Data: %d\n", data->type);
    // Add specific data fields here
    // For example, printf("Data: %d\n", data->value);
}



