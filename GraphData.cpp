//----------------------------------------------------------------------------
// GraphData.cpp
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

#include "GraphData.h"
using namespace std;

//------------------------------- Default Constructor -------------------------
// Preconditions:none
// Postconditions: a new GraphData object is created with data value "" 
// (empty string)
GraphData::GraphData()
{
	this->data = "";
}

//----------------------------- Constructor  ----------------------------------
// Preconditions:none
// Postconditions: a new GraphData object is created with the data value 
// equal to parameter s
GraphData::GraphData(string s)
{
	this->data = s;
}

//-------------------------------- Copy Constructor ---------------------------
// Makes a copy of a GraphData object
// Preconditions: sourceData GraphData object has a valid string value
// Postconditions: sourceData is copied into this->data
GraphData::GraphData(const GraphData &sourceData)
{
	this->data = sourceData.data;
}

//------------------------------------  =  ------------------------------------
// assignes GraphData object sourceData to *this (making a deep copy)
// Preconditions: character TreeData object has a valid ch value
// Postconditions: character is copied into *this
GraphData & GraphData::operator=(const GraphData &sourceData)
{
	this->data = sourceData.data;
	return *this;
}

//---------------------------------  <<  --------------------------------------
// Overloaded output operator for class TreeData; key is the TreeData object
// to be output.
// Preconditions: a TreeData object must have a valid character value ch
// Postconditions: the TreeData's value (char) is sent to the output w/o
// spaces.
ostream& operator<<(ostream& outStream, const GraphData &gData)
{
	outStream << gData.data.c_str();
	return outStream;
}

//-------------------------------- Destructor ---------------------------------
// Destructor for class GraphData
// Preconditions: none
// Postconditions: GraphData object is destructed appropriately
GraphData::~GraphData()
{
}
