/*
* Week 7, LPA course's Problem (BFS)
* University of Coimbra, 07.05.2016
* Author: Artur Pedroso
* License: WTFPL
*/

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <limits.h>
#include <string.h>

#define N 5000

struct Asset {
	int assetPower;
	unsigned short int numNeighbours;
	unsigned short int neighboursId[N];
};

struct State {
	unsigned short int id;
	int depth;
};

Asset assets[N+1];

int enemyBestPower, shortPathToEnemy;
char enemyFound;
char visitedAssets[N+1];

void initializeStateVars() {
	enemyBestPower = INT_MAX;
	shortPathToEnemy = INT_MAX;
	enemyFound = 0;
	memset(visitedAssets, 0, (N + 1) * sizeof(char));
}

void doSearch() {
	State currentState, newState;
	int localPowerSum;
	std::queue<State> assetsToVisitQueue;

	currentState.id = 1;
	currentState.depth = 0;
	assetsToVisitQueue.push(currentState);
	visitedAssets[1] = 1;

	while (!assetsToVisitQueue.empty()) {

		currentState = assetsToVisitQueue.front();
		assetsToVisitQueue.pop();
		
		if (assets[currentState.id].assetPower < 0) {
			//in this case it's an enemy
			
			enemyFound = 1;
			localPowerSum = assets[currentState.id].assetPower;
			
			for (int i = 0; i < assets[currentState.id].numNeighbours; i++) {
			
				//sum asset power of neightbours
				localPowerSum += assets[assets[currentState.id].neighboursId[i]].assetPower;

				if (!visitedAssets[assets[currentState.id].neighboursId[i]]) {
					//if neighbour asset wasn't visited mark it as visited and send it to queue
					visitedAssets[assets[currentState.id].neighboursId[i]] = 1;
					newState.id = assets[currentState.id].neighboursId[i];
					newState.depth = currentState.depth + 1;
					assetsToVisitQueue.push(newState);
				}
			
			}

			//update state vars if enemy local power is better
			if (localPowerSum < enemyBestPower) {
				enemyBestPower = localPowerSum;
				shortPathToEnemy = currentState.depth;
			}

		}
		else {
			//in this case it's an ally
			
			for (int i = 0; i < assets[currentState.id].numNeighbours; i++) {

				if (!visitedAssets[assets[currentState.id].neighboursId[i]]) {
					//if neighbour asset wasn't visited mark it as visited and send it to queue
					visitedAssets[assets[currentState.id].neighboursId[i]] = 1;
					newState.id = assets[currentState.id].neighboursId[i];
					newState.depth = currentState.depth + 1;
					assetsToVisitQueue.push(newState);
				}

			}

		}
		
	}

}

void printOutput() {
	if (enemyFound)
		printf("%d\n", shortPathToEnemy);
	else
		printf("No threats!\n");
}

int main() {
	/*freopen("test.txt", "r", stdin);
	freopen("test_out.txt", "w", stdout);*/
	int numAssets;
	
	while (scanf("%d", &numAssets) != EOF) {
		numAssets++;
		for (int i = 1; i < numAssets; i++) {
			scanf("%d", &assets[i].assetPower);
			scanf("%hu", &assets[i].numNeighbours);
			for (int j = 0; j < assets[i].numNeighbours; j++) {
				scanf("%hu", &assets[i].neighboursId[j]);
			}
		}

		initializeStateVars();

		doSearch();

		printOutput();
		
	}

	return 0;
}