#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define MAX_LEN 10

int dp[MAX_LEN+1][MAX_LEN+1];
int prices[MAX_LEN+1] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

int rod(int n, int remain_len){
	if (n == 0)
		return 0;

	if(dp[n][remain_len])
		return dp[n][remain_len];

	if (n > remain_len)
		return dp[n][remain_len] = rod(remain_len, remain_len);

	return dp[n][remain_len] = std::max(prices[n] + rod(n, remain_len-n), rod(n-1, remain_len));
}

int main(){
	for(int i = 1; i < MAX_LEN+1; i++){
		printf("Max gain cutting length %d of rod: %d.\n", i, rod(i, i));
		memset(dp, 0, sizeof(dp));
	}
	return 0;
}