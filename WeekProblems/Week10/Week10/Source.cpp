/*
**APL's course 
**10th Week problem (The problem is modulated as Max flow problem)
**University of Coimbra
**Artur Pedros 01-06-2016
**Licence: wtfpl
*/

//TODO: We could remove players that doesn't have a position assigned.

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <string.h>

#define N 600 
#define M 100

int nodesResidualCapacity[N + M + 2][N + M + 2]; //adjacency matrix for Residual Graph
int path[N + M + 2]; //path from s to t found with bfs... it should be traversed in reverse order, that is, s - t
bool marked[N + M + 2]; //marked nodes in bfs to avoid loops

//bfs that returns true if there exists a path from s to t
bool bfs(int s, int t) {
	memset(marked, 0, sizeof(bool)*(t+1));
	std::queue <int> q;
	q.push(s);
	marked[s] = true;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		if (node == t) {
			return true;
		}

		for (int i = 1; i <= t; i++) {
			if (nodesResidualCapacity[node][i] && !marked[i]) {
				marked[i] = true;
				q.push(i);
				path[i] = node;
			}
		}
	}
	return false;
}

//O(E^2*V)
void solveProblem(int s, int t) {
	int flow=0;
	while (bfs(s, t)) {
		flow++;
		//update residual network
		int i = t;
		while (i != s) {
			nodesResidualCapacity[path[i]][i]--;
			nodesResidualCapacity[i][path[i]]++;
			i = path[i];
		}
	}
	printf("%d\n", flow);
}

void buildProblemStructure(int numPlayers, int numPositions, int t) {
	int numPositionsPlayer;
	int playPosition;

	//connect s to all players
	for (int i = 1; i <= numPlayers; i++) {
		nodesResidualCapacity[0][i] = 1;
	}
	
	//create edges from players to positions with flow = 1
	for (int i = 1; i <= numPlayers; i++) {
		scanf("%d", &numPositionsPlayer);
		for (int j = 0; j < numPositionsPlayer; j++) {
			scanf("%d", &playPosition);
			nodesResidualCapacity[i][numPlayers + playPosition] = 1;
		}
	}

	//create edges from positions to t with flow = max num. of players allowed
	for (int j = 1; j <= numPositions; j++) {
		scanf("%d", &nodesResidualCapacity[numPlayers + j][t]);
	}
}

//zero padding nodesResidualCapacity
void resetResidualCapacity(int maxIndex) {
	for (int i = 0; i < maxIndex; i++) {
		for (int j = 0; j < maxIndex; j++)
			nodesResidualCapacity[i][j] = 0;
	}
}

int main() {
	//freopen("test.txt", "r", stdin);
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		int t = n+m+1;
		buildProblemStructure(n, m, t);
		solveProblem(0, t);
		resetResidualCapacity(t + 1);
	}
	return 0;
}
