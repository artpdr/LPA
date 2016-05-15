#include <cstdio>
#include <cstdlib>
#include <map>
#include <limits.h>

#define N 750

struct Connection {
    int num_connections;
    //city id
	int adjacent_city[N];
	//city distance
	long long int distance[N];
};

int n_roads, n_cities, max_weight;
long long int best;
int weights[N+1];
int visited[N+1];
bool path_found;
Connection connections[N+1];

void shortest_path(int city, long long int current_distance, int current_weight) {
	if (current_distance >= best)
		return;
	if (current_weight > max_weight)
		return;
	if (city == n_cities) {
		path_found = true;
		if (current_distance < best)
			best = current_distance;
		return;
	}
	for (int i = 0; i < connections[city].num_connections; i++) {
		if (!visited[connections[city].adjacent_city[i]]) {
			visited[connections[city].adjacent_city[i]] = 1;
			shortest_path(connections[city].adjacent_city[i], current_distance + connections[city].distance[i], current_weight + weights[connections[city].adjacent_city[i]]);
			visited[connections[city].adjacent_city[i]] = 0;
		}
	}
}

int main()
{
	int n_cases, city1, city2, distance;
	std::scanf("%d", &n_cases);
	while (n_cases--) {
		best = LONG_LONG_MAX;
		std::scanf("%d %d %d", &n_cities, &n_roads, &max_weight);

		for(int i = 1; i <= n_cities; i++){
            connections[i].num_connections = 0;
		}

		for (int i = 0; i < n_roads; i++) {
			std::scanf("%d %d %d", &city1, &city2, &distance);
			connections[city1].adjacent_city[connections[city1].num_connections] = city2;
			connections[city1].distance[connections[city1].num_connections] = distance;
			connections[city1].num_connections++;
			connections[city2].adjacent_city[connections[city2].num_connections] = city1;
            connections[city2].distance[connections[city2].num_connections] = distance;
			connections[city2].num_connections++;
		}
		for (int i = 1; i <= n_cities; i++) {
			std::scanf("%d", &(weights[i]));
		}
		path_found = false;
		int minimum_weight;
		if(n_cities != 1)
            minimum_weight = weights[1] + weights[n_cities];
		else
            minimum_weight = weights[0];
		weights[1] = 0;
		weights[n_cities] = 0;
		visited[1] = 1;
		shortest_path(1, 0, minimum_weight);
		if (path_found)
			printf("%lli\n", best);
		else
			printf("Bye Bye Natalia!\n");
	}
    return 0;
}
