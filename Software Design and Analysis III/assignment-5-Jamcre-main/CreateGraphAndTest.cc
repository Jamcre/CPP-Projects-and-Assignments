// NAME: James Michael Crespo
// DESCRIPTION: This file used to test the Graph class and Q1 of assignment

#include <iostream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv)
{
  // Read command line arguments, <GRAPH_FILE> and <ADJACENCY_QUERYFILE>
  string line, graphFilePath = argv[1], queryFilePath = argv[2];

  // Open input files
  ifstream graphFile(graphFilePath), queryFile(queryFilePath);

  // Declare variables
  int numVertices, source, destination;
  graphFile >> numVertices;
  Graph temp_graph(numVertices);
  float weight;

  // Check if graph file was successfully opened
  if (!graphFile)
  {
    cout << "Error opening graph file" << endl;
    return 1;
  }
  else
  {
    // Skip the first line of the graph file
    getline(graphFile, line);

    // Read graph edges from the file
    while (getline(graphFile, line))
    {
      istringstream iss(line);
      iss >> source;
      while (iss >> destination >> weight)
      {
        // Add edge to the graph
        temp_graph.setEdgeWeight(source, destination, weight);
      }
    }
  }

  // Check if query file was successfully opened
  if (!queryFile)
  {
    cout << "Error opening query file" << endl;
    return 1;
  }
  else
  {
    // Process queries from the file
    while (queryFile >> source >> destination)
    {
      if (temp_graph.checkAdjacency(source, destination))
      {
        cout << source << " " << destination << ": connected " << temp_graph.getEdgeWeight(source, destination) << endl;
      }
      else
      {
        cout << source << " " << destination << ": not_connected" << endl;
      }
    }
  }

  return 0;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_File>"
         << "<ADJACENCY_QUERYFILE>" << endl;
    return 0;
  }

  graphTestDriver(argc, argv);

  return 0;
}
