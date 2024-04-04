// WHicks_simulationProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "queuingSystemADT.h"
#include <iostream>
#include <random>
using namespace std;

int main()
{
    int timeUnits, transTime, arrivalTime, numServers;
    cout << "Input the length of the simulation, in units of time (use an integer): ";
    cin >> timeUnits;
    cout << endl << "Input the length of the customer-server transaction, in units of time (use an integer): ";
    cin >> transTime;
    cout << endl << "Input the average amount of time between customer arrivals, in units of time (use an integer): ";
    cin >> arrivalTime;
    cout << endl << "Input the number of servers to use (use an integer): ";
    cin >> numServers;
    cout << endl;

    queuingSystem simulation(timeUnits, transTime, arrivalTime, numServers);
    //queuingSystem.mainLoop();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
