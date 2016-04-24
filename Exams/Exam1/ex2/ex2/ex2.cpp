/*#include "stdafx.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <cstring>

int n_roads, n_cities, max_weight;
int distances[750][750], weights[750];
int short_distance[750], min_weights[750];
int minimum_weight;
bool sptSet[750];

/*Return index of the vertex with less distance from source*/
int minDistance() {
	int min = INT_MAX, min_index = -1;

	for (int v = 0; v < n_cities; v++)
		if (sptSet[v] == false && short_distance[v] <= min) {
			min = short_distance[v];
			min_index = v;
		}
	return min_index;
}

bool dijkstra() {
	for (int i = 0; i < n_cities; i++) {
		short_distance[i] = INT_MAX;
	}
	memset(sptSet, false, n_cities * sizeof(bool));
	
	
	short_distance[0] = 0;
	int sptSet_nElem = 0;
	
	while (sptSet_nElem++ < n_cities) {
		
		int u = minDistance();
		if (u < 0)
			return false;
		sptSet[u] = true;

		if (short_distance[u] == INT_MAX) {
			return false;
		}
		if (u == n_cities - 1) {
			return true;
		}

		for (int v = 0; v < n_cities; v++) {
			if (!sptSet[v] && distances[u][v] && short_distance[u] != INT_MAX
				&& short_distance[u] + distances[u][v] < short_distance[v]
				&& min_weights[u] + weights[v] <= max_weight) {
					min_weights[v] = min_weights[u] + weights[v];
					short_distance[v] = short_distance[u] + distances[u][v];
			}
		}
	}
	return false;
}

int main()
{
	/*freopen("test.txt", "r", stdin);*/
	int n_cases, city1, city2, distance;
	scanf("%d", &n_cases);
	while (n_cases--) {
		scanf("%d %d %d", &n_cities, &n_roads, &max_weight);
		for (int i = 0; i < n_cities; i++) {
			for (int j = 0; j < n_cities; j++) {
				distances[i][j] = 0;
			}
		}
		for (int i = 0; i < n_roads; i++) {
			scanf("%d %d %d", &city1, &city2, &distance);
			distances[--city1][--city2] = distance;
			distances[city2][city1] = distance;
		}
		for (int i = 0; i < n_cities; i++) {
			scanf("%d", &(weights[i]));
		}
		memset(min_weights, 0, n_cities * sizeof(int));
		minimum_weight = weights[0] + weights[n_cities - 1];
		weights[0] = 0;
		weights[n_cities - 1] = 0;
		min_weights[0] = minimum_weight;
		if (dijkstra())
			printf("%d\n", short_distance[n_cities-1]);
		else
			printf("Bye Bye Natalia!\n");
	}
    return 0;
}

