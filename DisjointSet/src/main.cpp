/*
 * main.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: Artur Pedroso
 * Description: Calculate Min Spanning Tree
 */
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>

#define MAXNODES 100

class Node{
public:
	Node* parent;
	int rank;
};

class Edge{
public:
	Node *x;
	Node *y;
	int weight;
};


struct LessThanByWeight
{
	bool operator()(const Edge& lhs, const Edge& rhs) const
	{
		return lhs.weight > rhs.weight;
	}
};

class DisjointSet{
public:
	//construct sets with just one element
	void makeSet(Node* node){
		node->parent = node;
		node->rank = 0;
	}

	//join x and y node's sets if they are different
	bool unionSet(Node* x, Node* y){
		x = findSet(x);
		y = findSet(y);
		if (x == y)
			return false;

		if(x->rank > y->rank){
			y->parent = x;
			return true;
		}

		if(x->rank < y->rank){
			x->parent = y;
			return true;
		}

		y->parent = x;
		x->rank++;

		return true;
	}

	Node* findSet(Node* node){
		if(node->parent == node)
			return node;
		node->parent = findSet(node->parent);
		return node->parent;
	}
};

std::priority_queue<Edge, std::vector<Edge>, LessThanByWeight> edges;
int numNodes;
DisjointSet ds;
Node* nodes[MAXNODES];
int mstWeight;

//first line gives the number of nodes
//each line has the id of the node that the node of that line connects to, followed by the weight. The line ends when 0 is read.
//the numeration of nodes start at 1.
void readInput(){
	int adjNode, weight;
	scanf("%d", &numNodes);

	if (numNodes > MAXNODES){
		printf("Maximum number of nodes is: %d\n", numNodes);
		exit(-1);
	}

	//make nodes and disjoint set
	for (int i = 0; i < numNodes; i++){
		nodes[i] = (Node*) malloc(sizeof(Node));
		nodes[i]->rank = 0;
		ds.makeSet(nodes[i]);
	}

	//make edges queue ordered by weight CRESC
	for(int i = 0; i < numNodes; i++){
		scanf("%d", &adjNode);
		if(adjNode > 0){
			do{
			    scanf("%d", &weight);
			    Edge e;
			    e.x=nodes[i];
			    e.y=nodes[adjNode-1];
			    e.weight = weight;
			    edges.push(e);
			    scanf("%d", &adjNode);
			}while(adjNode > 0);
		}
	}
}

void findMST(){
	mstWeight = 0;
	while(!edges.empty()){
		if(ds.unionSet(edges.top().x, edges.top().y)){
			mstWeight += edges.top().weight;
		}
		edges.pop();
	}

	printf("MST Total Weight: %d\n", mstWeight);
}

int main(){
	freopen("test.txt", "r", stdin);
	readInput();
	findMST();
	return 0;
}
