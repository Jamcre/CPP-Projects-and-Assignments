// NAME: James Michael Crespo
// DESCRIPTION: This file used to test the Dijkstra and Q2 of assignment

#include <iostream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

int pathfindDriver(int argc, char **argv)
{
  // Read command line arguments, <GRAPH_FILE> and <STARTING_VERTEX>
  string graphFilePath = argv[1];
  int start = stoi(argv[2]);

  // Initialize empty graph
  Graph temp_graph(0);

  // Read the graph from the file
  vector<vector<pair<int, float>>> adjacency_lists = temp_graph.processGraph(graphFilePath);

  // Find the shortest paths using the Dijkstra's algorithm function
  vector<float> dist = temp_graph.dijkstraShortestPaths(start, adjacency_lists);

  return 0;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_FILE>"
         << "<STARTING_VERTEX>" << endl;
    return 0;
  }

  pathfindDriver(argc, argv);

  return 0;
}
