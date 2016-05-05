#include <stdio.h>
#include <stdlib.h>
#include <queue>

#define N 5000

struct Asset {
	unsigned short int id;
	int power;
	unsigned short int numNeighbours;
	unsigned short int neighbours[N];
};

struct State {
	unsigned short int id;
	int depth;
};

Asset assets[N+1];

int bestPower, shortPath;

int main() {

	return 0;
}