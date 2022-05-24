// ---------------------------------------------- DinitzAlgorithm.cpp -------------------------------------------------

// Name and Class: Tim Denisiuk CSS 449
// Code Use: Used to implement functions for DinitzAlgorithm
// Creation Date: 05/19/2022
// Last Modified: 05/24/2022
// --------------------------------------------------------------------------------------------------------------------

//Purpose: Defines all functions for DinitzAlgorithm
//Functionality: Adjacency matrix stores edges, which implicitly stores nodes	
//Assumptions: The text file given will always have the same format to it
// -------------------------------------------------------------------------------------------------------------------- 

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include "DinitzAlgorithm.h"

using namespace std;

//Constructor
//Default constructor for the class
//Precondition: None
//Postcondition: Initializes class values
DinitzAlgorithm::DinitzAlgorithm()
{
	numNodes = 0;
}

//Destructor
//Default destructor for the class
//Precondition: None
//Postcondition: None, since nothing is dynamically allocated
DinitzAlgorithm::~DinitzAlgorithm()
{ }

//createGraphs
//Sets up the flow graph, residual graph, and level graph
//Precondition: Given input file must be formatted correctly
//Postcondition: Initializes each graph to be modified later
void DinitzAlgorithm::createGraphs(ifstream& file)
{
	int from, to, numEdges;

	file >> numNodes;

	names.resize(numNodes + 1);
	FG.resize(numNodes + 2);
	for (int i = 0; i <= numNodes + 1; i++)
	{
		FG[i].resize(numNodes + 2);
	}

	for (int i = 1; i < numNodes + 1; i++)
		file >> names[i];

	for (int i = 0; i <= numNodes + 1; i++)	
		for (int j = 0; j <= numNodes + 1; j++)		
			FG[i][j] = INT_MAX;								//INT_MAX is used as infinity, which means no edge

		
	RG = LG = FG;											//Empty blank slate for all graphs

	file >> numEdges;
	for (int i = 0; i < numEdges; i++)						//Setting up graphs
	{
		file >> from;
		file >> to;
		FG[from][to] = 0;
		RG[from][to] = 1;
	}


	for (int i = 1; i <= (numNodes / 2); i++)
	{
		FG[0][i] = 0;
		FG[(numNodes / 2) + i][numNodes + 1] = 0;
		RG[0][i] = 1;
		RG[(numNodes / 2) + i][numNodes + 1] = 1;
	}
}

//performAlgorithm
//Performs Dinitz's algorithm
//Precondition: createGraphs must be called before performAlgorithm
//Postcondition: Performs the algorithm for matching
void DinitzAlgorithm::performAlgorithm() 
{
	stack<int> path;
	int location, retreatFrom, retreatTo;
	bool done = false, stuck = true;
	bool result;
	while (1)
	{
		result = createLevelGraph();			//Construct level graph, returns a bool to tell whether path exists or not

		if (result == false)					//No path from source to sink, would be done
			break;

		location = 0;							//Initialize location to source, path to empty
		while (!path.empty())
			path.pop();
		path.push(0);							//Path will always start from 0

		while (!path.empty())					//If path is empty, it means it is stuck at source
		{
			if (location == numNodes + 1)			//Path ends at sync
			{				
				augmentGraphs(path, FG, RG, LG);
				path.push(0);							//Resets 
				location = 0;
				continue;
			}
			for (int i = 1; i <= numNodes + 1; i++)		//Finds next path based on current location
			{		
				if (LG[location][i] == 1)
				{					
					location = i;
					path.push(location);
					stuck = false;							//Found a path
					break;
				}
			}

			if (stuck == false)								//If it finds the path, stuck will change to false. Changes to true prepare for next node
				stuck = true;
			
			else
			{
				if (location == 0)							//Stuck at source
					break;
				retreatFrom = path.top();
				path.pop();
				retreatTo = path.top();
				LG[retreatTo][retreatFrom] = INT_MAX;
				location = retreatTo;
				
			}
		}
	}

	displayResults(FG);
}

//createLevelGraph
//Creates a level graph based on the current residual graph
//Precondition: None
//Postcondition: Modifies LG to create a new level graph
bool DinitzAlgorithm::createLevelGraph()
{
	int start = 0;
	bool found = false;
	set<int> queued;												//Set used to quickly check if node has been queued for BFS
	queue<int> next;
	
	next.push(0);
	queued.insert(0);
	while (!next.empty())
	{
		start = next.front();
		next.pop();
		for (int i = 0; i < numNodes + 2; i++)
		{
			if (RG[start][i] != INT_MAX)
			{		
				if (i == numNodes + 1)									//If a path exists to sync, sets found to true to show path exists
					found = true;

				if (queued.count(i) == 0 && i != numNodes + 1)			//Queues nodes to be used in BFS
				{
					next.push(i);
					queued.insert(i);
				}
				LG[start][i] = 1;
			}
		}
	}
	return found;
}

//augmentGraphs
//Augments the different graphs whenever a path to the sync is found
//Precondition: None
//Postcondition: Changes all three graphs based on path to sync
void DinitzAlgorithm::augmentGraphs(stack<int>& path, vector<vector<int>>& FG, vector<vector<int>>& RG, vector<vector<int>>& LG) const
{
	int to = path.top();
	path.pop();
	int from = path.top();
	
	while (!path.empty())
	{
		LG[from][to] = INT_MAX;
		RG[from][to] = INT_MAX;
		RG[to][from] = 1;

		if (from < to)
			FG[from][to] = 1;
		else
			FG[to][from] = 0;

		to = path.top();
		path.pop();
		if (path.empty())
			break;
		from = path.top();
	}
}

//displayResults
//Displays the matching results
//Precondition: None
//Postcondition: Displays the result in the console
void DinitzAlgorithm::displayResults(vector<vector<int>>& FG) const
{
	int matches = 0;
	for (int i = 1; i <= (numNodes / 2); i++)
	{
		for (int j = (numNodes / 2) + 1; j <= numNodes; j++)
		{
			if (FG[i][j] == 1)												//If flow exists, then it is matched
			{
				cout << names[i] << " / " << names[j] << endl;
				matches++;
			}

		}
	}

	if (matches != 1)
		cout << matches << " total matches" << endl;
	else
		cout << matches << " match total" << endl;
}