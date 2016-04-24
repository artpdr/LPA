#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

struct connection {
	int adjacent_city;
	int distance;
};

int n_roads, n_cities, max_weight, best;
int weights[750];
char visited[750];
bool path_found;
std::vector <connection> distances[750];

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
	for (std::vector<connection>::iterator it = distances[city].begin(); it != distances[city].end(); ++it) {
		if (!visited[it->adjacent_city]) {
			visited[it->adjacent_city] = 1;
			shortest_path(it->adjacent_city, current_distance + it->distance, current_weight + weights[it->adjacent_city]);
			visited[it->adjacent_city] = 0;
		}
	}
}

int main()
{
	int n_cases, city1, city2, distance;
	connection tmp;
	std::scanf("%d", &n_cases);
	while (n_cases--) {
		best = 0;
		std::scanf("%d %d %d", &n_cities, &n_roads, &max_weight);
		for (int i = 0; i < n_roads; i++) {
			std::scanf("%d %d %d", &city1, &city2, &distance);
			tmp.adjacent_city = --city2;
			tmp.distance = distance;
			distances[--city1].push_back(tmp);
			tmp.adjacent_city = city1;
			tmp.distance = distance;
			distances[city2].push_back(tmp);
			best += distance;
		}
		for (int i = 0; i < n_cities; i++) {
			std::scanf("%d", &(weights[i]));
		}
		path_found = false;
		int minimum_weight = weights[0] + weights[n_cities - 1];
		weights[0] = 0;
		weights[n_cities - 1] = 0;
		visited[0] = 1;
		shortest_path(0, 0, minimum_weight);
		if (path_found)
			printf("%d\n", best);
		else
			printf("Bye Bye Natalia!\n");
		
		for (int i = 0; i < n_cities; i++) {
			distances[i].clear();
		}
	}
    return 0;
}