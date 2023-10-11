#include <iostream>
#include <stdio.h>
#include "Examples.hpp"

using namespace std;

int main() 
{
    std::cout << "--------------------RTES QoSQueuing------------------------"<<endl;
    std::cout << "A Real Time Embedded System Project for QoS Queuing"<<endl;
    std::cout << "Developed by: Francesco Sartor & Marco Francesco Sette"<<endl;

    int mainchoice, history_policy;
    int N_WRITERS, N_READERS, MAX_SIZE, N_WRITER_ITERATIONS, N_READER_ITERATIONS;

    do
        {
            std::cout << "Choose an option:\n";
            std::cout << "1. Run the example (history: keep all(max=10), depth: unused)\n";
            std::cout << "2. Choose your own parameteres and run the example\n";
            std::cout << "3. Choose your own parameters and work on your own\n";
            std::cout << "4. Exit\n";
            std::cout << "Your choice: ";
            std::cin >> mainchoice;
            if(mainchoice < 1 || mainchoice > 4)
                std::cout << "Invalid choice. Try again......\n";
        }while(mainchoice < 1 || mainchoice > 4);

        switch(mainchoice)
        {
            case 1:
                std::cout << "Running the example with default parameters (15 writers and 15 readers, 10 max size, 10 iterations for each writer and reader)\n";
                Queue_test();
                break;

            case 2:
                std::cout << "Choose the number of writers: ";
                std::cin >> N_WRITERS;
                std::cout << "Choose the number of readers: ";
                std::cin >> N_READERS;
                std::cout << "What's your history policy? 1. Keep all 2. Keep last: \n";
                std::cin >> history_policy;
                if(history_policy == 1)
                {
                    std::cout << "Choosing the default (10) for your queue depth...\n";
                    MAX_SIZE = 10;
                }
                else
                {
                    std::cout << "What's your depth? \n";
                    std::cin >> MAX_SIZE;
                }
                std::cout << "Choose the number of iterations for each writer: ";
                std::cin >> N_WRITER_ITERATIONS;
                std::cout << "Choose the number of iterations for each reader: ";
                std::cin >> N_READER_ITERATIONS;
                std::cout << "Running the example with your parameters\n";
                Queue_test2(N_WRITERS, N_READERS, MAX_SIZE, N_WRITER_ITERATIONS, N_READER_ITERATIONS);
                break;

            case 3:
                break;
        
            case 4:
                std::cout << "Exiting\n";
                break;
        
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }    
    return 0;
}
