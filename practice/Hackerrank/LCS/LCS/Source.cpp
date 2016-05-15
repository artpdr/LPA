#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#define N 100

int seqASize, seqBSize;
int seqA[N+1], seqB[N+1];
int dp[N+1][N+1];

void lcs() {
	int max = 0;
	for (int i = 1; i <= seqASize; i++) {
		for (int j = 1; j <= seqBSize; j++) {
			
			if (seqA[i] == seqB[j]) 
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

		}
	}

}

void reconstructLCS(int i, int j) {
	if (i == 0 || j == 0)
		return;
	
	while (dp[i][j] == dp[i][j - 1]) {
		j--;
	}

	if (seqA[i] == seqB[j]) {
		reconstructLCS(i - 1, j - 1);
		printf("%d ", seqA[i]);
	}
	else {
		reconstructLCS(i - 1, j);
	}
}

int main() {
	scanf("%d %d", &seqASize, &seqBSize);

	for (int i = 1; i <= seqASize; i++) {
		scanf("%d", &seqA[i]);
	}

	for (int i = 1; i <= seqBSize; i++) {
		scanf("%d", &seqB[i]);
	}

	lcs();

	reconstructLCS(seqASize, seqBSize);

	return 0;
}