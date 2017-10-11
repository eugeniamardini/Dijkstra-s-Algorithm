//----------------------------------------------------------------------------
// GraphData.h
// Author: Yauheniya Zapryvaryna CSS 343 Winter 2015 UWB
//----------------------------------------------------------------------------
// DESCRIPTION: Class GraphData implements an abstract data type held by Graph's
//			   vertices.The GraphData is represented by the string data type.
// FUNCTIONALITY: 
//	--outputs the GraphData object to the console;
//	--creates a deep copy of one GraphData object 
// ASSUMPTIONS:
//	--text file to be read by the program is correctly formatted
//	--in overloaded operator<<, a GraphData object is displayed with no 
//	  surrounding spaces.
//-----------------------------------------------------------------------------

#pragma once
#include <string>
#include <fstream>
using namespace std;

class GraphData
{
//-----------------------------  <<  --------------------------------------
// Overloaded output operator for class TreeData; key is the TreeData object
// to be output.
// Preconditions: a TreeData object must have a valid character value ch
// Postconditions: the TreeData's value (char) is sent to the output w/o
// spaces.
friend ostream& operator<<(ostream& outStream, const GraphData &gData);
public:

	//-------------------------------Default Constructor-----------------------
	// Preconditions:none
	// Postconditions: a new GraphData object is created with data value "" 
	// 9empty string)
	GraphData();

	//-----------------------------Constructor---------------------------------
	// Preconditions:none
	// Postconditions: a new GraphData object is created with the data value 
	// equal to parameter s
	GraphData(string );

	//--------------------------------Copy Constructor-------------------------
	// Makes a copy of a GraphData object
	// Preconditions: sourceData GraphData object has a valid string value
	// Postconditions: sourceData is copied into this->data
	GraphData(const GraphData &);

	//----------------------------------  =  ----------------------------------
	// assignes GraphData object sourceData to *this (making a deep copy)
	// Preconditions: character TreeData object has a valid ch value
	// Postconditions: character is copied into *this
	GraphData & operator=(const GraphData &);

	//---------------------------- Destructor ---------------------------------
	// Destructor for class GraphData
	// Preconditions: none
	// Postconditions: GraphData object is destructed appropriately
	~GraphData();

private:
	string data;
};

