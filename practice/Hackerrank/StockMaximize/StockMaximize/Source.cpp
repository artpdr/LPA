#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_DAYS 50000
#define MAX_PRICE 100000

int nDays, prices[MAX_DAYS];
int dp[MAX_DAYS];

int maxProfit(int day, int shares) {
	if (day == nDays) {
		//return max for last day
		return shares * prices[day];
	}

	int max, tmpMax;



	//buy share
	max = maxProfit(day+1, shares+1) - prices[day];

	//don't buy and don't sell
	tmpMax = maxProfit(day + 1, shares);

	if (tmpMax > max)
		max = tmpMax;

	//sell everything
	tmpMax = maxProfit(day + 1, 0) + shares * prices[day];
	
	if (tmpMax > max)
		max = tmpMax;
	


	return max;
	
}

int main() {
	freopen("test.txt", "r", stdin);
	freopen("test_out.txt", "w", stdout);

	int numTests;
	
	scanf("%d", &numTests);
	while (numTests--) {
		scanf("%d", &nDays);
		for (int i = 0; i < nDays; i++) {
			scanf("%d", &prices[i]);
			dp[i] = 0;
		}

		nDays--;

		printf("%d\n", maxProfit(0, 0));
	}
	
	return 0;
}
