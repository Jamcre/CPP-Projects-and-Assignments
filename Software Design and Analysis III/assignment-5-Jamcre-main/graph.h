// NAME: James Michael Crespo
// DESCRIPTION: This file contains the implementation for the Graph class
#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

class Graph
{
public:
    /**
     * Constructer, makes space for total_vertices in adjacency_lists, '+ 1' b/c it is one indexed
     * @param total_vertices: total number of vertices in graph object
     * @return: intialized Graph object
     */
    Graph(int total_vertices)
    {
        adjacency_lists_.resize(total_vertices + 1);
    }

    /**
     * Sets weight of specified edge in graph
     * @param start_vertex: starting vertex of edge
     * @param end_vertex: ending vertex of edge
     * @param weight: weight of edge
     */
    void setEdgeWeight(int start_vertex, int end_vertex, float weight)
    {
        adjacency_lists_[start_vertex][end_vertex] = weight;
    }

    /**
     * Gets weight of specified edge in graph
     * @param start_vertex: starting vertex of edge
     * @param end_vertex: ending vertex of edge
     * @return: weight of edge
     */
    float getEdgeWeight(int start_vertex, int end_vertex)
    {
        return adjacency_lists_[start_vertex][end_vertex];
    }

    /**
     * Checks adjacency between two vertices
     * @param start_vertex: starting vertex
     * @param end_vertex: ending vertex
     * @return: True if the vertices are adjacent, False otherwise
     */
    bool checkAdjacency(int start_vertex, int end_vertex)
    {
        // If end_vertex exists in the adjacency list of start_vertex, the vertices are adjacent
        if (adjacency_lists_[start_vertex].count(end_vertex) != 0)
        {
            return true;
        }
        return false;
    }

    /**
     * Makes adjacency list using info in line from query file.
     * @param query_file_line: The line from the query file containing vertex-weight pairs.
     * @return: The complete adjacency list with end vertices and edge weights.
     */
    vector<pair<int, float>> makeAdjacencyList(const string &query_file_line)
    {
        // Initialize variables, iss object, and temporary adjacency list
        int end_vertex;
        float edge_weight;
        istringstream iss(query_file_line);
        vector<pair<int, float>> temp_adjacency_list;
        // Populate adjacency list with read-in info and return complete adjacency list
        while (iss >> end_vertex >> edge_weight)
        {
            temp_adjacency_list.emplace_back(end_vertex, edge_weight);
        }
        return temp_adjacency_list;
    }

    /**
     * Processes graph info described in txt file, and makes adjacency lists with the info
     * @param query_filename: Name of file with graph info
     * @return: Adjancency lists for the provided graph
     */
    vector<vector<pair<int, float>>> processGraph(string query_filename)
    {
        // Open query file and initialize line reader
        ifstream query_file(query_filename);
        string query_file_line;
        // Read 1st line which has total vertices in graph, and makes space in vect of adjanceny list
        getline(query_file, query_file_line);
        int total_vertices = stoi(query_file_line);
        vector<vector<pair<int, float>>> temp_adjacency_lists(total_vertices + 1); // '+ 1' b/c it is one indexed
        // Read-in all starting vertices, followed by end_vertices and their weights
        while (getline(query_file, query_file_line))
        {
            // Create object for line, and get current start_vertex and following info.
            istringstream iss(query_file_line);
            int curr_vert;
            iss >> curr_vert;
            // Get reference to the adjacency list of the current start vertex
            vector<pair<int, float>> &curr_vert_adj_list = temp_adjacency_lists[curr_vert];
            // Create the adjacency list using the rest of line
            curr_vert_adj_list = makeAdjacencyList(query_file_line.substr(query_file_line.find(' ') + 1));
        }
        // Return completed adjancey list with all vertices, with their end vertices and edge weights
        return temp_adjacency_lists;
    }

    /**
     * Helper function to print the shortest paths from a vertex to the start vertex.
     * @param vertex: Current vertex
     * @param start_vertex: Starting vertex
     * @param other_vertices: Vector with other vertices in shortest path for each vertex.
     * @param distances: Vector of distances from start vertex to other vertices.
     */
    void printPathHelper(int vertex, int start_vertex, const vector<int> &other_vertices, const vector<float> &distances)
    {
        if (vertex == start_vertex)
        {
            // If the vertex is the starting vertex itself, print it with a cost of 0
            cout << vertex << ": " << vertex << " cost: " << fixed << setprecision(1) << 0.0 << endl;
        }
        else if (distances[vertex] == numeric_limits<float>::max())
        {
            // If there is no valid path to the target vertex, indicate it as "not possible"
            cout << vertex << ": not_possible" << endl;
        }
        else
        {
            cout << vertex << ": ";
            vector<int> path;
            int current_vertex = vertex;
            while (current_vertex != start_vertex)
            {
                // Traverse the path from current_vertex to start_vertex and store the vertices in a vector
                path.push_back(current_vertex);
                current_vertex = other_vertices[current_vertex];
            }
            // Print the path in the correct order
            cout << start_vertex << " ";
            for (int i = path.size() - 1; i >= 0; i--)
            {
                cout << path[i];
                if (i != 0)
                    cout << " ";
            }
            cout << " cost: " << fixed << setprecision(1) << distances[vertex] << endl;
        }
    }

    /**
     * Prints the shortest paths from a start vertex to all other vertices.
     * @param start_vertex: The starting vertex
     * @param other_vertices: Vector with other vertices in shortest path for each vertex.
     * @param distances: Vector of distances from start vertex to other vertices.
     */
    void printShortestPaths(int start_vertex, const vector<int> &other_vertices, const vector<float> &distances)
    {
        for (int end_vertex = 1; end_vertex < distances.size(); end_vertex++)
        {
            printPathHelper(end_vertex, start_vertex, other_vertices, distances);
        }
    }

    /**
     * Calculates the shortest paths from a start vertex to all other vertices using Dijkstra's algorithm.
     * @param start_vertex: The starting vertex.
     * @param adjacency_lists: Adjancency lists for graph
     * @return: Vector of distances from the start vertex to all other vertices.
     */
    vector<float> dijkstraShortestPaths(int start_vertex, const vector<vector<pair<int, float>>> &adjacency_lists)
    {
        // Get total number of vertices in graph
        int total_vertices = adjacency_lists.size();
        // Initialize distances vector with maxi distances, and other_vertices vector with -1
        vector<float> distances(total_vertices, numeric_limits<float>::max());
        vector<int> other_vertices(total_vertices, -1);
        // Set distance of the start_vertex to 0
        distances[start_vertex] = 0;
        // Create a priority_queue(from binary_heap.h) to process vertices based on distances
        BinaryHeap<pair<float, int>> priority_queue;
        // Insert start_vertex with distance of 0 into priority_queue
        priority_queue.insert(make_pair(0, start_vertex));

        // Dijkstra's algorithm main loop
        while (!priority_queue.isEmpty())
        {
            // Extract vertex with shortest distance from priority_queue
            int current_vertex = priority_queue.findMin().second; // '.second' access vertex from returned pair by findMin()
            priority_queue.deleteMin();                           // Remove

            // Get current distance from distances vector
            float current_distance = distances[current_vertex];

            // Skip if the extracted distance is greater than stored distance for current vertex
            if (current_distance > distances[current_vertex])
                continue;

            // Process neighboring vertices of current_vertex
            for (const auto &[next_vertex, weight] : adjacency_lists[current_vertex])
            {
                // Calculate new distance from start_vertex to the next_vertex
                float new_distance = distances[current_vertex] + weight;

                // Update distances and other_vertices vectors if new distance is smaller
                if (new_distance < distances[next_vertex])
                {
                    distances[next_vertex] = new_distance;
                    other_vertices[next_vertex] = current_vertex;
                    priority_queue.insert(make_pair(new_distance, next_vertex));
                }
            }
        }
        // Print the shortest paths using the printShortestPaths function, and return distances
        printShortestPaths(start_vertex, other_vertices, distances);
        return distances;
    }

private:
    /**
     * Vector of unordered_map representing adjacency lists for vertices.
     * Each unordered_map has the vertex's adajcent vertices and corresponding weight.
     * Key = Connected vertex.
     * Value = Edge weight
     */
    vector<unordered_map<int, float>> adjacency_lists_;
};

#endif