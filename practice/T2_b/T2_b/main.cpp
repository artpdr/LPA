#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define MAX_VALUE_IN_ONE_BAG 100*500/2

int coins[100];
int dp[100][MAX_VALUE_IN_ONE_BAG+1];

int knapsack(int coin, int max_val) {
	if (coin < 0 || max_val == 0)
		return 0;

	if (dp[coin][max_val])
		return dp[coin][max_val];

	if (coins[coin] > max_val)
		return dp[coin][max_val] = knapsack(coin - 1, max_val);
	
	else
		return dp[coin][max_val] = std::max(knapsack(coin-1, max_val), knapsack(coin-1, max_val-coins[coin]) + coins[coin]);
}

int main() {
	int n_cases, n_coins;
	std::scanf("%d", &n_cases);
	while (n_cases--) {
		std::scanf("%d", &n_coins);
		int coins_sum = 0;
		for (int i = 0; i < n_coins; i++) {
			std::scanf("%d", &(coins[i]));
			coins_sum += coins[i];
		}
		if (n_coins > 0) {
			int half_value = coins_sum/2;
			int max_half_value = knapsack(n_coins-1, half_value);
			printf("%d\n", coins_sum - 2*max_half_value);
		}
		else
			printf("0\n");
	}
}