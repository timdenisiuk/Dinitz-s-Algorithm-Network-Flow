# Program Project 3: Dinitz Algorithm

## Project Background

This project requires the implementation of Dinit'z Algorithm, which is an extension of the Ford-Fulkerson Algorithm. This algorithm deals
with graphs, and the overall concept of network flow. The problem is finding the total number of matches from a bipartite graph. 

## Project Description

To find a match, we first create a level graph to see if there is a path from the beginning to the end. If there is, we know we have a valid matching
and we can start traversing the level graph. If we find a path from the beginning (source) to the end (sync), we remove the path from the level graph,
while altering the flow of the residual graph and the flow graph. One we perform the algorithm, we attempt to do it again, and see if there is a path.
Each invocation of the algorithm with result in another matching.
