#include <vector>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define DISTANCE 6

struct Node {
	std::vector <int> connections;
};

struct State {
	int id;
	int depth;
};

Node nodes[N];
int distances[N];
int numNodes;
char visited[N];

void shortestPath(int start) {
	std::queue<State> states;
	State currentState, newState;
	visited[start] = 1;
	currentState.id = start;
	currentState.depth = 0;
	states.push(currentState);
	
	for (int i = 0; i < numNodes; i++) {
		distances[i] = -1;
	}

	while (!states.empty()) {
		currentState = states.front();
		states.pop();
		distances[currentState.id] = currentState.depth;
		for (std::vector<int>::iterator it = nodes[currentState.id].connections.begin(); it != nodes[currentState.id].connections.end(); it++) {
			if (!visited[*it]) {
				visited[*it] = 1;
				newState.id = *it;
				newState.depth = currentState.depth + DISTANCE;
				states.push(newState);
			}
		}
	}
}

void printResult() {
	for (int i = 0; i < numNodes; i++) {
		if(distances[i] != 0)
			printf("%d ", distances[i]);
	}
	printf("\n");
}

void deleteVectors() {
	for (int i = 0; i < numNodes; i++) {
		nodes[i].connections.clear();
	}
}

int main() {
	int numTests, numEdges, nodeX, nodeY;
	scanf("%d", &numTests);

	while (numTests--) {
		scanf("%d", &numNodes);
		scanf("%d", &numEdges);

		for (int i = 0; i < numEdges; i++) {
			scanf("%d %d", &nodeX, &nodeY);
			nodes[nodeX-1].connections.push_back(nodeY-1);
			nodes[nodeY-1].connections.push_back(nodeX-1);
		}

		scanf("%d", &nodeX);

		shortestPath(nodeX-1);

		//delete vectors
		deleteVectors();
		memset(visited, 0, numNodes * sizeof(char));
		//print output
		printResult();
	}

	return 0;
}