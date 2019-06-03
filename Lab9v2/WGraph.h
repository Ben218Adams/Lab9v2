#pragma once

#include <string>

struct Edge
{
	int endIndex;
	Edge* next;
	int weight;
};

class edgeComparator		// allows edge comparison by weight
{
public: 
	int operator() (const Edge& e1, const Edge& e2)
	{
		return e1.weight > e2.weight;
	}
};

struct Node
{
	char name;
	bool visited;
	Edge* connects;
};


class WGraph
{
public:
	WGraph()
	{
		numNodes = 0;	// initialize number of nodes in list
		for (int i = 0; i < SIZE; i++)	// initialize nodeList to nullptrs
			this->nodeList[i] = nullptr;	// Adding Curlys here 
		for (int i = 0; i < SIZE; i++)	// set up edge Matrix to start with no edges
			for (int j = 0; j < SIZE; j++)
				this->edgeMatrix[i][j] = { 0 };		// Adding Curlys here 
	}
	virtual ~WGraph()
	{
		// delete all connections from each node in nodeList
		for (int i = 0; i < numNodes; i++)
		{
			// similar to destructor on linked list
			Edge* ptr = nodeList[i]->connects;
			while (ptr != nullptr)
			{
				Edge* temp = ptr;
				ptr = ptr->next;
				delete temp;
			}
		}
	}

	void addNode(char name);
	bool addWEdge(char starts, char ends, int weight);

	std::string listNodes();
	std::string displayWEdges();
	std::string displayMatrix();
	std::string displayUnvisited();
	std::string minCostTree(char start);

	std::string breadthFirst(char name);
	std::string recBreadthFirst(Node * tempNode);
	std::string depthFirst(char name);
	std::string recDepthFirst(Node * tempNode);

private:
	static const int SIZE = 20;
	int numNodes;
	Node* nodeList[SIZE];
	int edgeMatrix[SIZE][SIZE];

	int findNode(char name);
	void resetVisited();
};

