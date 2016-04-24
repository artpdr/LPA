#include <cstdlib>
#include <cstdio>
#include <cstring>

long int path[101][101];
int x_dim, y_dim;

long int solve(int x, int y) {
	if (x > x_dim || y > y_dim)
		return 0;

	if (path[y_dim - y][x] != -1)
		return path[y_dim - y][x];

	path[y_dim - y][x] = solve(x+1,y) + solve(x,y+1);

	return path[y_dim-y][x];
}

int main() {
	//freopen("test.txt", "r", stdin);
	bool exit = false;
	while (!exit) {
		scanf("%d %d", &x_dim, &y_dim);
		for (int i = 0; i <= y_dim; i++)
			for (int j = 0; j <= x_dim; j++)
				path[i][j] = -1;
		if (x_dim && y_dim) {
			//set house to arrive = 1
			path[0][x_dim] = 1;
			int wolf_loc;
			scanf("%d", &wolf_loc);
			int x_loc, y_loc;
			while (wolf_loc--) {
				scanf("%d %d", &x_loc, &y_loc);
				path[y_dim - y_loc][x_loc] = 0;
			}
			solve(0, 0);
			if (path[y_dim][0] > 1) {
				printf("There are %ld paths from Little Red Riding Hood's house to her grandmother's house.\n", path[y_dim][0]);
			}
			else if (path[y_dim][0] == 1) {
				printf("There is one path from Little Red Riding Hood's house to her grandmother's house.\n");
			}
			else
				printf("There is no path.\n");
		}
		else {
			exit = true;
		}
	}
	return 0;
}