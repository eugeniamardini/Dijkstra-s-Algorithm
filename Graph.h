//----------------------------------------------------------------------------
// Graph.h
// Author: Yauheniya Zapryvaryna CSS 343 Winter 2015 UWB
//----------------------------------------------------------------------------
// DESCRIPTION: Class Graph implements Implement Dijkstra's shortest path 
// algorithm, including recovering the paths. 
// FUNCTIONALITY: 
//	--uses an adjacency list to store the edges
//	--finds lowest cost paths by using a 2D array
//	--displays the cost and path from every vertex to every other vertex in a 
//	  specific format
//	--can output one particular path in detail 
//	--reads data from a file
//	--inserts an edge into a graph, replacing the previous edge that existed 
//	  between the two vertices
// ASSUMPTIONS:
//	--text file to be read by the program contains properly formatted info
//	  the graph can contain no more than 100 vertices
//	--user is responsible to call findShortestPath() in order to "update"
//	  the look of the grapth's output, if the insertEdge() or removeEdge()
//	  were called after the original shortest path search occurred.
//	--the graph contains no negative values of weights or vertices
//-----------------------------------------------------------------------------

#pragma once
#include <iostream>
#include "GraphData.h"

class Graph 
{                            
public:

	//-------------------------------Default Constructor-----------------------
	// Preconditions:none
	// Postconditions: a new Graph object is created with size '0'; the 
	// adjecency list and a table get initialized;
	Graph();

	//--------------------------------Copy Constructor-------------------------
	// makes a deep copy of a graph
	// Preconditions: srcGraph must be allocated in memory
	// Postconditions: srcGrapth is copied into this graph 9as well as its 
	// table)
	Graph(const Graph &);

	//-------------------------------- buildGraph -----------------------------
	// Builds a graph by reading data from an ifstream
	// Preconditions: infile has been successfully opened and the file contains
	// properly formated data (according to the program specs)
	// Postconditions: One graph is read from infile and stored in the object
	void buildGraph(ifstream &);

	//-------------------------------- insertEdge -----------------------------
	// Inserts an edge into a graph
	// Preconditions: Grapth object is allocated in memory; src is within the
	// size limits of a current object
	// Postconditions: an edge is inserted into a graph if its source is within
	// size limits, replacing any previous edge between the vertices
	void insertEdge(int , int ,int );

	//------------------------------  removeEdge  -----------------------------
	// Removes one occurrence of a character from the BST. 
	// Preconditions: src and dest are non-negative integers and src is within 
	// the graph's size limits
	// Postconditions: the edge is removed from the graph
	void removeEdge (int, int);

	//------------------------- findShortestPath  -----------------------------
	// Performs Dijkstra's algorithm and finds the shortest path from every 
	// vertex to every other vertex
	// Preconditions: the graph object is allocated and properly initialized
	// Postconditions: the 2D table (array) is filled in with shortest paths & 
	// their weights
	void findShortestPath();

	//-----------------------------  displayAll  ------------------------------
	// Outputs the contents of the Grapht o the console in the table 
	// format, required by the assignment specs(source followed by destination, 
	// distance, and the shortest path).
	// Preconditions: Graph object is allocated in memory and is not empty
	// Postconditions: the constents of the Graph and its shortest path table
	// get output to to console.
	void displayAll();

	//-----------------------------  display  ---------------------------------
	// Outputs the detailed description for the Graph's path to console in a 
	// format, required by the assignment specs(source followed by destination, 
	// distance, and the shortest path; follwed by the names of each vertex in 
	// a path on a separate line).
	// Preconditions: Graph object is allocated in memory
	// Postconditions: the Graph path's distance gets output to the console, 
	// followed by the shortest path, received through calling a helper methods 
	// displayPath and dispalyPathWithDescriptions
	void display(int ,int);

	//-------------------------------- clear ----------------------------------
	// Empties the Graph
	// Preconditions: none
	// Postconditions: the Graph's memory is appropriately deallocated
	void clear();

	//---------------------------- Destructor ---------------------------------
	// Destructor for class Graph
	// Preconditions: none
	// Postconditions: Graph is destructed, memory occupied previously by the graph
	// is deallocated
	~Graph();
	
private:
	static const int MAX_VERTICES = 101;

	struct EdgeNode {			
		int adjVertex;			// subscript of the adjacent vertex 
		int weight;				// weight of edge
		EdgeNode *nextEdge;
	};

	struct VertexNode {
		EdgeNode *edgeHead;		// head of the list of edges
		GraphData *data;		// store vertex data here
	};

	// array of VertexNodes
	VertexNode vertices[MAX_VERTICES];
	
	// table of information for Dijkstra's algorithm
	struct Table {
		bool visited;			// whether vertex has been visited
		int dist;				// shortest known distance from source
		int path;				// previous vertex in path of min dist
	};
	int size;					// number of vertices in the graph
	Table T[MAX_VERTICES][MAX_VERTICES];
								// stores visited, distance, path -
								// two dimensional in order to solve
								// for all sources

	//------------------------------  initializeAdjList  ----------------------
	// Initializes the Graph object (represented by an adjacency list) to the
	// default values
	// Preconditions: the Graph object must be allocated
	// Postconditions: the Graph's adjacency list is properly initialized to 
	// default values (edgeHead of a linked list at vertex[i] is initialiazed 
	// to NULL). 
	void initializeAdjList();

	//------------------------------  initializeTable  ------------------------
	// Initializes the Table (2D array) to default values
	// Preconditions: the Graph object must be allocated
	// Postconditions: the Graph's Table is properly initialized to default 
	// values
	void initializeTable();

	//-------------------------------- displayPath  ---------------------------
	// Outputs the numerical description for the Graph's path to the console
	// Preconditions: Graph object is allocated in memory
	// Postconditions: the Graph's shortest path  gets displayed on the console
	void displayPath(int ,int );

	//--------------------- - displayPathWithDescriptions  --------------------
	// Outputs the detailed description for the Graph's path to the console
	// Preconditions: Graph object is allocated in memory
	// Postconditions: the Graph's shortest path descriptional names get 
	// displayed on the console
	void displayPathWithDescriptions(int , int);
   };

