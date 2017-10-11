//----------------------------------------------------------------------------
// Graph.cpp
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

#include <fstream>
#include <iostream>
#include <string> 
#include "Graph.h"
using namespace std;

//-------------------------------Default Constructor-----------------------
// Preconditions:none
// Postconditions: a new Graph object is created with size '0'; the adjecency
// list and a table get initialized;
Graph::Graph()
{
	size = 0;
	this->initializeAdjList();
	this->initializeTable();
}


//------------------------------  initializeTable  ----------------------------
// Initializes the Table (2D array) to default values
// Preconditions: the Graph object must be allocated
// Postconditions: the Graph's Table is properly initialized to default values
void Graph::initializeTable()
{
	for (int src = 1; src <= size; src++)
	{
		for (int v = 1; v <= size; v++)
		{
			T[src][v].dist = INT_MAX;
			T[src][v].path = 0;
			T[src][v].visited = false;
		}
	}
}

//------------------------------  initializeAdjList  --------------------------
// Initializes the Graph object (represented by an adjacency list) to the
// default values
// Preconditions: the Graph object must be allocated
// Postconditions: the Graph's adjacency list is properly initialized to 
// default values (edgeHead of a linked list at vertex[i] is initialiazed to 
// NULL). 
void Graph::initializeAdjList()
{
	for (int i = 1; i < MAX_VERTICES; i++)
	{
		vertices[i].edgeHead = NULL;
	}
}

//--------------------------------Copy Constructor----------------------------
// makes a deep copy of a graph
// Preconditions: srcGraph must be allocated in memory
// Postconditions: srcGrapth is copied into this graph 9as well as its table)
Graph::Graph(const Graph &srcGraph)
{
	for (int index = 1; index <= srcGraph.size; index++)
	{
		this->size = srcGraph.size;
		this->vertices[index].data = srcGraph.vertices[index].data;
		EdgeNode *orig = srcGraph.vertices[index].edgeHead;
		if (orig == NULL)
		{
			this->vertices[index].edgeHead = NULL;
		}
		else
		{
			this->vertices[index].edgeHead = new EdgeNode;
			this->vertices[index].edgeHead->adjVertex = srcGraph.vertices[index].edgeHead->adjVertex;
			this->vertices[index].edgeHead->weight = srcGraph.vertices[index].edgeHead->weight;
			EdgeNode *cur = this->vertices[index].edgeHead;
			orig = orig->nextEdge;
			while (orig != NULL)
			{
				cur->nextEdge = new EdgeNode;
				cur->nextEdge->adjVertex = orig->adjVertex;
				cur->nextEdge->weight = orig->weight;
				cur = cur->nextEdge;
				orig = orig->nextEdge;
			}
			cur->nextEdge = NULL;
		}
		for (int dest = 1; dest <= srcGraph.size; dest++)
		{
			this->T[index][dest].path = srcGraph.T[index][dest].path;
			this->T[index][dest].dist = srcGraph.T[index][dest].dist;
			this->T[index][dest].visited = srcGraph.T[index][dest].visited;
		}
	}
}

//-------------------------------- buildGraph ---------------------------------
// Builds a graph by reading data from an ifstream
// Preconditions:  infile has been successfully opened and the file contains
// properly formated data (according to the program specs)
// Postconditions: One graph is read from infile and stored in the object
void Graph::buildGraph(ifstream& infile) {

	infile >> size;                          // data member stores array size
	if (infile.eof())
		return;
	infile.ignore();                         // throw away '\n' go to next line
	string vertexName;
	// get descriptions of vertices
	for (int v = 1; v <= size; v++)
	{
		getline(infile, vertexName, '\n');
		GraphData *newData = new GraphData(vertexName);
		vertices[v].data = newData;         // store appropriately
	}
	// fill cost edge array
	int src = 1, dest = 1, cost = 1;
	for (;;)
	{
		infile >> src >> dest >> cost;
		if (src == 0 || infile.eof())
			break;
		insertEdge(src, dest, cost);
	}
}

//-------------------------------- insertEdge ---------------------------------
// Inserts an edge into a graph
// Preconditions: Grapth object is allocated in memory; src is within the size 
// limits of a current object
// Postconditions: an edge is inserted into a graph if its source is within
// size limits, replacing any previous edge between the vertices
void Graph::insertEdge(int src, int dest, int cost)
{
	EdgeNode *edgeN = new EdgeNode;
	edgeN->adjVertex = dest;
	edgeN->weight = cost;
	if (src >= 1 && src <= size)
	{
		if (vertices[src].edgeHead == NULL ||
			edgeN->adjVertex <= vertices[src].edgeHead->adjVertex)
		{
			edgeN->nextEdge = vertices[src].edgeHead;
			vertices[src].edgeHead = edgeN;
		}
		else
		{
			EdgeNode *cur = vertices[src].edgeHead;
			while (cur->nextEdge != NULL &&
				cur->nextEdge->adjVertex < edgeN->adjVertex)
			{
				cur = cur->nextEdge;
			}
			edgeN->nextEdge = cur->nextEdge;
			cur->nextEdge = edgeN;
		}
	}
}

//------------------------------  removeEdge  ---------------------------------
// Removes one occurrence of a character from the BST. 
// Preconditions: src and dest are non-negative integers and src is within the 
// graph's size limits
// Postconditions: the edge is removed from the graph
void Graph::removeEdge(int src, int dest)
{
	if (src >= 1 && src <= size)
	{
		while (this->vertices[src].edgeHead != NULL &&
			this->vertices[src].edgeHead->adjVertex == dest)
		{
			EdgeNode * temp = this->vertices[src].edgeHead;
			this->vertices[src].edgeHead = this->vertices[src].edgeHead->nextEdge;
			delete temp;
		}
		if (this->vertices[src].edgeHead == NULL)
		{
			return;
		}
		for (EdgeNode *cur = this->vertices[src].edgeHead;
			cur->nextEdge != NULL; cur = cur->nextEdge)
		{
			while (cur->nextEdge != NULL && cur->nextEdge->adjVertex == dest)
			{
				EdgeNode * temp = cur->nextEdge;
				cur->nextEdge = temp->nextEdge;
				delete temp;
			}
		}
	}
}

//------------------------- findShortestPath  ---------------------------------
// Performs Dijkstra's algorithm and finds the shortest path from every vertex 
// to every other vertex
// Preconditions: the graph object must be allocated and properly initialized
// Postconditions: the 2D table (array) is filled in with shortest paths and 
// their weights
void Graph::findShortestPath()
{
	this->initializeTable();
	int src, minIndex;
	for (int vertex = 1; vertex <= size; vertex++)
	{
		src = vertex;
		T[src][src].dist = 0;
		T[src][src].path = -1;
		for (int n = 1; n < size; n++)
		{
			int i = 0;
			int  minDist = INT_MAX;
			for (i = 1; i <= size; i++)
			{
				if (T[src][i].visited == false && T[src][i].dist <= minDist)
				{
					minDist = T[src][i].dist;
					minIndex = i;
				}
			}
			T[src][minIndex].visited = true;
			EdgeNode *cur = vertices[minIndex].edgeHead;
			while (cur != NULL && vertices[src].edgeHead != NULL)
			{
				if (T[src][cur->adjVertex].visited == false )
				{
					if (minDist + cur->weight < T[src][cur->adjVertex].dist)
					{
						T[src][cur->adjVertex].dist = cur->weight + minDist;
						T[src][cur->adjVertex].path = minIndex;
					}
				}
				cur = cur->nextEdge;
			}
		}
	}
}

//-----------------------------  displayAll  ---------------------------------
// Outputs the contents of the Grapht o the console in the table 
// format, required by the assignment specs (source followed by destination, 
// distance, and the shortest path).
// Preconditions: Graph object is allocated in memory and is not empty
// Postconditions: the constents of the Graph and its shortest path table
// get output to to console.
void Graph::displayAll()
{
	cout << "Description\t\t\t" << "From\t" << "To\t" <<
		"Distance   " << "Path" << endl;
	for (int src = 1; src <= size; src++)
	{
		cout << *this->vertices[src].data << endl;
		for (int dest = 1; dest <= size; dest++)
		{
			if (T[src][dest].path != -1)
			{
				cout << "\t\t\t\t";
				cout << src << "\t" << dest << "\t";
				if (T[src][dest].dist == INT_MAX || T[src][dest].dist < 0)
				{
					cout << "--" << endl;
				}
				else
				{
					cout << T[src][dest].dist << "\t   ";
					displayPath(src, dest);
					cout << endl;
				}
			}
		}
	}
}

//-----------------------------  display  ------------------------------------
// Outputs the detailed description for the Graph's path to the console in a 
// format, required by the assignment specs (source followed by destination, 
// distance, and the shortest path; follwed by the names of each vertex in a 
// path on a separate line).
// Preconditions: Graph object is allocated in memory
// Postconditions: the Graph path's distance gets output to the console, 
// followed by the shortest path, received through calling a helper methods 
// displayPath and dispalyPathWithDescriptions
void Graph::display(int src, int dest)
{
	if (src < 1 || src > size || dest < 1 || dest > size)
	{
		return;
	}
	else
	{
		cout << src << "\t" << dest << "\t";
		if (T[src][dest].dist == INT_MAX || T[src][dest].dist < 0)
		{
			cout << "--" << endl;
		}
		else
		{
			cout << T[src][dest].dist << "\t   ";
			displayPath(src, dest);
			cout << endl;
			displayPathWithDescriptions(src, dest);
		}
	}
}

//--------------------- - displayPathWithDescriptions  ------------------------
// Outputs the detailed description for the Graph's path to the console
// Preconditions: Graph object is allocated in memory
// Postconditions: the Graph's shortest path descriptional names get displayed
// on the console
void Graph::displayPathWithDescriptions(int src, int dest)
{
	if (T[src][dest].path == -1)
	{
		cout << *this->vertices[src].data << "  " << endl;
	}
	else
	{
		displayPathWithDescriptions(src, T[src][dest].path);
		cout << *this->vertices[dest].data << "  " << endl;
	}
}

//-------------------------------- displayPath  ------------------------------
// Outputs the numerical description for the Graph's path to the console
// Preconditions: Graph object is allocated in memory
// Postconditions: the Graph's shortest path  gets displayed on the console
void Graph::displayPath(int src, int dest)
{
	if (T[src][dest].path == -1)
	{
		cout << src << "  ";
	}
	else
	{
		displayPath(src, T[src][dest].path);
		cout << dest << "  ";
	}
}

//-------------------------------- clear -------------------------------------
// Empties the Graph
// Preconditions: none
// Postconditions: the Graph's memory is appropriately deallocated
void Graph::clear()
{
	for (int src = 1; src < size; src++)
	{
		EdgeNode *temp = new EdgeNode;
		temp = this->vertices[src].edgeHead;
		while (temp != NULL)
		{
			temp = this->vertices[src].edgeHead->nextEdge;
			this->vertices[src].edgeHead = NULL;
			this->vertices[src].edgeHead = temp;
		}
		delete temp;
		temp = NULL;
	}
}

//---------------------------- Destructor -------------------------------------
// Destructor for class Graph
// Preconditions: none
// Postconditions: Graph is destructed, memory occupied previously by the graph
// is deallocated
Graph::~Graph()
{
	this->clear();
}