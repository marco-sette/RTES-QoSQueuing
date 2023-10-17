/*
** RTES-QoSQueuing: main.cpp - Main file for RTES-QoSQueuing
** ==========================================================================
** RTES-QoSQueuing - A simple RTES-QoSQueuing implementation for Linux
** ==========================================================================
** Authors: Francesco Sartor, Marco Francesco Sette
** Real-Time and Embedded Systems Project - University of Modena and Reggio Emilia
** Prof. Marko Bertogna and Prof. Paolo Burgio
** A.Y. 2022-2023
*/

#include <iostream>
#include <stdio.h>
#include "QoSAccess.hpp"

using namespace std;

int main() 
{
    std::cout << "--------------------RTES QoSQueuing------------------------"<<endl;
    std::cout << "A Real Time Embedded System Project for QoS Queuing"<<endl;
    std::cout << "Developed by: Francesco Sartor & Marco Francesco Sette"<<endl;

    int mainchoice, history_policy;
    int N_WRITERS, N_READERS, MAX_SIZE;

    do
        {
            std::cout << "Choose an option:\n";
            std::cout << "1. Run the example (history: keep all(max=10), depth: unused)\n";
            std::cout << "2. Choose your own parameteres and run the example\n";
            std::cout << "3. Exit\n";
            std::cout << "Your choice: ";
            std::cin >> mainchoice;
            if(mainchoice < 1 || mainchoice > 3)
                std::cout << "Invalid choice. Try again......\n";
        }while(mainchoice < 1 || mainchoice > 3);

        switch(mainchoice)
        {
            case 1:
                std::cout << "Running the example with default parameters (15 writers and 15 readers, 10 max size, 10 iterations for each writer and reader)\n";
                Queue_test();
                break;

            case 2:
                std::cout << "Choose the number of writers (must be greater or equal the number of readers): ";
                std::cin >> N_WRITERS;
                if(N_WRITERS <= 0){
                    std::cout << "Invalid choice.\n";
                    return 1;
                }
                std::cout << "Choose the number of readers: ";
                std::cin >> N_READERS;
                if(N_READERS <= 0 || N_READERS > N_WRITERS){
                    std::cout << "Invalid choice.\n";
                    return 1;
                }
                std::cout << "What's your history policy? 1. Keep all 2. Keep last: ";
                std::cin >> history_policy;
                if(history_policy == 1)
                {
                    std::cout << "Choosing the default (10) for your queue depth...\n";
                    MAX_SIZE = 10;
                }
                else if (history_policy == 2)
                {
                    std::cout << "What's your depth? ";
                    std::cin >> MAX_SIZE;
                    if(MAX_SIZE <= 0){
                        std::cout << "Invalid choice.\n";
                        return 1;
                    }
                }
                else
                {
                    std::cout << "Invalid choice.\n";
                    return 1;
                }
                std::cout << "Running the example with your parameters\n";
                Queue_test2(N_WRITERS, N_READERS, MAX_SIZE);
                break;

            case 3:
                std::cout << "Exiting\n";
                break;
        
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    return 0;
}
