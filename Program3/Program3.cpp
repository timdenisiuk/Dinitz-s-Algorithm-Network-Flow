// ------------------------------------------------ Program3.cpp ------------------------------------------------------

// Name and Class: Tim Denisiuk CSS 449
// Code Use: Driver for the program
// Creation Date: 05/19/2022
// Last Modified: 05/24/2022
// --------------------------------------------------------------------------------------------------------------------

//Purpose: Driver for the program
//Functionality: Creates the DinitzAlgorithm class and uses it to perform the algorithm		
//Assumptions:
// -------------------------------------------------------------------------------------------------------------------- 

#include <iostream>
#include <fstream>
#include "DinitzAlgorithm.h"

using namespace std;

//main
//main driver for the program
//Precondition: None
//Postcondition: performs the algorithm for Program 3
int main()
{
    ifstream infile ("program3data.txt");
    DinitzAlgorithm DA;
    DA.createGraphs(infile);
    DA.performAlgorithm();
    
}
