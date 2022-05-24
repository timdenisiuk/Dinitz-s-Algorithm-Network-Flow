// ------------------------------------------------ DinitzAlgorithm.h -----------------------------------------------------

// Name and Class: Tim Denisiuk CSS 449
// Code Use: Used to store adjacency matrixes to represents graphs
// Creation Date: 05/19/2022
// Last Modified: 05/24/2022
// --------------------------------------------------------------------------------------------------------------------

//Purpose: DinitzAlgorithm stores the graphs as adjacency matrix's using vectors
//Functionality: Each adjacency matrix stores each edge, which implicitly stores nodes		
//Assumptions: The text file given will always have the same format to it
// -------------------------------------------------------------------------------------------------------------------- 

#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <stack>

using namespace std;

class DinitzAlgorithm
{
public:
	//Constructor
	//Default constructor for the class
	//Precondition: None
	//Postcondition: Initializes class values
	DinitzAlgorithm();

	//Destructor
	//Default destructor for the class
	//Precondition: None
	//Postcondition: None, since nothing is dynamically allocated
	~DinitzAlgorithm();

	//createGraphs
	//Sets up the flow graph, residual graph, and level graph
	//Precondition: Given input file must be formatted correctly
	//Postcondition: Initializes each graph to be modified later
	void createGraphs(ifstream&);

	//performAlgorithm
	//Performs Dinitz's algorithm
	//Precondition: createGraphs must be called before performAlgorithm
	//Postcondition: Performs the algorithm for matching
	void performAlgorithm();

	//createLevelGraph
	//Creates a level graph based on the current residual graph
	//Precondition: None
	//Postcondition: Modifies LG to create a new level graph
	bool createLevelGraph();

	//augmentGraphs
	//Augments the different graphs whenever a path to the sinc is found
	//Precondition: None
	//Postcondition: Changes all three graphs based on path to sync
	void augmentGraphs(stack<int>&, vector<vector<int>>&, vector<vector<int>>&, vector<vector<int>>&) const;

	//displayResults
	//Displays the matching results
	//Precondition: None
	//Postcondition: Displays the result in the console
	void displayResults(vector<vector<int>>&) const;
	
private:
	vector<vector<int>> FG; //Flow Graph
	vector<vector<int>> RG;	//Residual Graph
	vector<vector<int>> LG;	//Level Graph
	vector<string> names;	//string to holds names
	int numNodes;			//int for number of nodes
	
};