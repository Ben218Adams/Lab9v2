
#include "WGraph.h"

#include <stdexcept>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <vector>

// add a new node to the graph
// only failure is if graph arrays are full
void WGraph::addNode(char name)
{
	// alternately, double the size of everything and start over
	if (numNodes >= SIZE)
		throw std::overflow_error("Graph size exceeded!!");

	// create a node with this name
	// initialize it with no edges and not yet visited
	Node * temp = new Node;
	temp->name = name;
	temp->visited = false;
	temp->connects = nullptr;

	// add to the list of nodes in graph
	nodeList[numNodes++] = temp;
}


// add a new edge to the graph
// return false and do nothing if either end is invalid
// otherwise add to both nodes edge lists and to the matrix
bool WGraph::addWEdge(char starts, char ends, int weight)
{
	if (starts == ends)
		return false;

	int startIndex = findNode(starts);
	int endIndex = findNode(ends);

	if (startIndex == -1 or endIndex == -1)
		return false;

	// set both links in edgeMatrix since non-directed graph	// changed '1' to "weight"
	edgeMatrix[startIndex][endIndex] = weight;
	edgeMatrix[endIndex][startIndex] = weight;		

	// create two new edges (one for each direction)
	// and add one to each nodes list of edges
	Edge * startEnd = new Edge;
	startEnd->endIndex = endIndex;
	startEnd->next = nullptr;
	startEnd->next = nodeList[startIndex]->connects;
	nodeList[startIndex]->connects = startEnd;
	
	Edge * endStart = new Edge;			// del all this if directed graph
	endStart->endIndex = startIndex;	//and this
	endStart->next = nullptr;			// and this
	endStart->next = nodeList[endIndex]->connects; //and this
	nodeList[endIndex]->connects = endStart;		//and this

	startEnd->weight = endStart->weight = weight; // last weight is the new one input to each direction weight

	return true;
}


// linear search for a node with this name
// return -1 if not found
// otherwise return its index in the nodeList
int WGraph::findNode(char name)
{
	for (int i = 0; i < numNodes; i++)
		if (nodeList[i]->name == name)
			return i;
	return -1;
}


// listing of nodes in the order
// they were added to the graph
std::string WGraph::listNodes()
{
	std::string theList = "The Nodes are: ";
	for (int i = 0; i < numNodes; i++)
	{
		theList += nodeList[i]->name;
		theList += " ";
	}
	return theList;
}


// for each node in graph,
// display its edges, using the edgelist
std::string WGraph::displayWEdges()
{
	std::stringstream ss;
	ss << "The EdgeList is: (Node: its edges : weight )\n";

	for (int i = 0; i < numNodes; i++)
	{
		// add the node name to the display
		ss << nodeList[i]->name;
		ss << ": ";

		// walk down its list of edges and add them also
		Edge* ptr = nodeList[i]->connects;
		while (ptr != nullptr)
		{
			ss << nodeList[ptr->endIndex]->name;
			ss << ":";
			ss << ptr->weight; 
			ss << " ";
			ptr = ptr->next;
		}
		// end this line of output
		ss << std::endl;
	}
	return ss.str();
}


// display the adjacency matrix
// as 0 for no connection and 1 for connection
std::string WGraph::displayMatrix()
{
	std::stringstream ss;
	ss << "The edgeMatrix is: \n";

	// output header line of destinations
	ss << std::setw(2) << " ";
	for (int i = 0; i < numNodes; i++)
		ss << std::setw(4) << nodeList[i]->name;
	ss << std::endl;

	// now output the array
	for (int i = 0; i < numNodes; i++)
	{
		// add the starting node
		ss << std::setw(2) << nodeList[i]->name;

		// now add its connections
		for (int j = 0; j < numNodes; j++)
			ss << std::setw(4) << edgeMatrix[i][j];

		// end the row
		ss << std::endl;
	}
	return ss.str();
}

std::string WGraph::displayUnvisited()
{
	std::string buff = "";
	for (int i = 0; i < SIZE / 2; i++)
	{
		if (nodeList[i]->visited == false)
		{
			buff += nodeList[i]->name;		
		}
	}
	return buff;
}

std::string WGraph::minCostTree(char start)
{
	//the PQ technique stolen from geeksforgeeks.org
	//
	std::string buff = "";
	int startKey = findNode(start);
	Node * startNode =nodeList[startKey];
	startNode->visited = true; 

	std::priority_queue <Edge, std::vector<Edge>, edgeComparator > pq;

	// walk down its list of edges and add them also
	Edge* ptr = nodeList[startKey]->connects;	

	while (ptr != nullptr)	// adds all connected edges to pq
	{
		pq.push(*ptr);
		ptr = ptr->next;
	}

	while (!pq.empty())
	{
		//see jims pdf
	}

	return buff;
}

std::string WGraph::depthFirst(char name)
{
	std::string buffer = "Depth first traversal starting at ";
	buffer += name;
	buffer += "\n";
	buffer += recDepthFirst(nodeList[findNode(name)]);
	buffer += "\n";
	buffer += "Unvisited nodes: " + displayUnvisited();
	resetVisited();
	return buffer;
}

std::string WGraph::recDepthFirst(Node * tempNode)		// Uses the recursive call stack as stack
{
	std::string buffer = "";

	int nodeKey = findNode(tempNode->name);
	nodeList[nodeKey]->visited = true;	// start node visited
	buffer += tempNode->name;

	for (int i = 0; i < SIZE / 2; i++)
	{
		if ((edgeMatrix[nodeKey][i] == 1) && (nodeList[i]->visited == false))	// looks at all connections to top
		{
			buffer += recDepthFirst(nodeList[i]);
		}
	}
	return buffer;
}



// breadth first traversal
// starts at a given node
// outputs a list of nodes visited
// and a list of any unreached nodes
std::string WGraph::breadthFirst(char name)
{
	std::string buffer = "Breadth first traversal starting at ";
	buffer += name;
	buffer += "\n";
	//////
	Node* tempNode = nodeList[findNode(name)];

	std::queue<Node*> myqueue;

	int nodeKey = findNode(tempNode->name);		// nodeKey
	buffer += tempNode->name;
	myqueue.push(tempNode);

	while (!myqueue.empty())
	{
		Node* top = myqueue.front();
		myqueue.pop();
		buffer += top->name;
		top->visited = true;
		nodeKey = findNode(top->name);

		for (int i = 0; i < SIZE; i++)
		{
			if ((edgeMatrix[nodeKey][i] == 1) && (nodeList[i]->visited == false))
				myqueue.push(nodeList[i]);
		}
	}

	//////
	buffer += "\n";
	buffer += "Unvisited nodes: " + displayUnvisited();
	resetVisited();
	return buffer;
}


//Z and K repeat twice
std::string WGraph::recBreadthFirst(Node * tempNode)	// recursive func calls			
{
	std::stringstream recBuff;

	if (tempNode != nullptr)
	{
		std::queue<Node*> myqueue;

		tempNode->visited = true;
		int nodeKey = findNode(tempNode->name);		// nodeKey
		recBuff << tempNode->name << " ";
		for (int i = 0; i < SIZE; i++)
		{
			if ((edgeMatrix[nodeKey][i] == 1) && (nodeList[i]->visited == false))
				myqueue.push(nodeList[i]);
		}
		while (!myqueue.empty())
		{
			Node* top = myqueue.front();
			myqueue.pop();
			recBuff << recBreadthFirst(top);
		}
	}
	else
		recBuff << "";
	return recBuff.str();
}

// helper function to reset all nodes to not visited
void WGraph::resetVisited()
{
	for (int i = 0; i < numNodes; i++)
		nodeList[i]->visited = false;
}

