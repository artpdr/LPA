// ex2_.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <vector>



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
		}
		for (int i = 0; i < n_cities; i++) {
			scanf("%d", &(weights[i]));
		}
		path_found = false;
		int minimum_weight = weights[0] + weights[n_cities - 1];
		weights[0] = 0;
		weights[n_cities - 1] = 0;
		visited[n_cities - 1] = 1;
		if (find_greedy_best(n_cities - 1, 0, minimum_weight)) {
			visited[n_cities - 1] = 0;
			visited[0] = 1;
			shortest_path(0, 0, minimum_weight);
			visited[0] = 0;
		}
		if (path_found)
			printf("%d\n", best);
		else
			printf("Bye Bye Natalia!\n");
	}
	return 0;
}

