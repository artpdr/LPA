#include <stdlib.h>
#include <stdio.h>

#define M 50
#define N 250

int coins[M];
long long int dp[M][N+1];

long long int ways(int coin, int change) {
	if (change < 0 || coin < 0)
		return 0;

	if (change == 0)
		return 1;

	if (dp[coin][change])
		return dp[coin][change];

	return dp[coin][change] = ways(coin, change-coins[coin]) + ways(coin-1, change);
}

int main() {
	int change, numCoins;

	scanf("%d", &change);
	scanf("%d", &numCoins);

	for (int i = 0; i < numCoins; i++) {
		scanf("%d", &coins[i]);
	}

	printf("%lld\n", ways(numCoins-1, change));
	return 0;
}