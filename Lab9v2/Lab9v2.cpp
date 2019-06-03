// Dis is main
// Ben Adams 
// Lab 999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
//
//
//
//  main.cpp
//  Weighted Graph
//
//  Created by Jim Bailey on 11/25/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//
// This demonstrates the methods of the simple graph class

#include <iostream>

#include "WGraph.h"

using namespace std;


int main()
{
	// create empty graph
	WGraph tree;

	// Add nodes to tree
	tree.addNode('A');
	tree.addNode('C');
	tree.addNode('T');
	tree.addNode('Z');
	tree.addNode('X');
	tree.addNode('K');
	tree.addNode('Q');
	tree.addNode('J');
	tree.addNode('M');
	tree.addNode('U');

	cout << "The nodes are: \n";
	cout << tree.listNodes() << endl << endl;

	// add edges to the tree
	tree.addWEdge('A', 'C', 3);
	tree.addWEdge('A', 'T', 4);
	tree.addWEdge('A', 'Z', 2);
	tree.addWEdge('X', 'C', 4);
	tree.addWEdge('C', 'K', 8);
	tree.addWEdge('T', 'Q', 4);
	tree.addWEdge('K', 'Q', 3);
	tree.addWEdge('Q', 'J', 6);
	tree.addWEdge('J', 'M', 5);
	tree.addWEdge('Z', 'X', 6);

	cout << "The edge list is: \n";
	cout << tree.displayWEdges() << endl << endl;

	cout << "The adjacency or edge matrix is: \n";
	cout << tree.displayMatrix() << endl << endl;

	cout << "The min-cost tree starting at Q is: \n";
	//cout << tree.minCostTree('Q') << endl;


	return 0;
}
