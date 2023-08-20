#include <iostream>
#include <stdio.h>
#include "Examples.h"

int main() {
    
    std::cout << "RTES Project" << std::endl;

    std::cout << "Testing writing on the queue" << std::endl;
    WRITE_EXAMPLE();

    std::cout << "Testing reading from the queue" << std::endl;
    READ_EXAMPLE();

    //std::cout << "Test: Hello World!" << std::endl;
    return 0;
}
