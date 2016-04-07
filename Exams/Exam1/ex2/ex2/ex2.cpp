/*#include "stdafx.h"*/
#include <stdlib.h>
#include <stdio.h>

int n_roads, n_cities, max_weight, best;
int distances[750][750], weights[750];
char visited[750];
bool path_found;
/*
bool find_greedy_best(int city, int current_distance, int current_weight) {
	if (current_weight > max_weight)
		return false;
	if (city == 0) {
		best = current_distance;
		path_found = true;
		return true;
	}
	for (int i = n_cities - 2; i > -1; i--) {
		if (distances[i][city] && !visited[i]) {
			visited[i] = 1;
			if (find_greedy_best(i, current_distance + distances[i][city], current_weight + weights[i])) {
				visited[i] = 0;
				return true;
			}
			visited[i] = 0;
		}
	}
	return false;
}*/

void shortest_path(int city, int current_distance, int current_weight) {
	if (current_distance >= best)
		return;
	if (current_weight > max_weight) 
		return;
	if (city == n_cities - 1) {
		path_found = true;
		if (current_distance < best)
			best = current_distance;
		return;
	}
	for (int i = 1; i < n_cities; i++) {
		if (!visited[i] && distances[city][i]) {
			visited[i] = 1;
			shortest_path(i, current_distance+distances[city][i], current_weight+weights[i]);
			visited[i] = 0;
		}
	}
}

int main()
{
	int n_cases, city1, city2, distance;
	scanf("%d", &n_cases);
	while (n_cases) {
		n_cases--;
		best = 0;
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
			best += distance;
		}
		for (int i = 0; i < n_cities; i++) {
			scanf("%d", &(weights[i]));
		}
		path_found = false;
		int minimum_weight = weights[0] + weights[n_cities - 1];
		weights[0] = 0;
		weights[n_cities - 1] = 0;
		/*visited[n_cities - 1] = 1;
		if (find_greedy_best(n_cities-1, 0, minimum_weight)) {
			visited[n_cities - 1] = 0;*/
			visited[0] = 1;
			shortest_path(0, 0, minimum_weight);
			/*visited[0] = 0;*/
		/*}*/
		if (path_found)
			printf("%d\n", best);
		else
			printf("Bye Bye Natalia!\n");
	}
    return 0;
}

