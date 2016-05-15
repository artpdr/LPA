/*Longest Increasing sequence exercise*/

#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int sequence[N];
int sequenceLength;
int count;
int dp[N];

int l(int i) {
	//count++;
	
	if (dp[i])
		return dp[i];
	
	/*if (i == 0)
		return dp[i] = 1;*/

	int tmpMax, max = 0;
	for (int j = 0; j < i; j++) {
		if (sequence[i] > sequence[j]) {
			tmpMax = l(j);
			if (tmpMax > max)
				max = tmpMax;
		}
	}

	//return max;
	return dp[i] = 1+max;
}

int lis(int n) {
	int max = 0, tmpMax;
	dp[0] = 1;
	for (int i = 1; i < n; i++) {
		tmpMax = l(i);
		if (tmpMax > max)
			max = tmpMax;
	}
	return max;
}

int lisBU() {
	int max;
	dp[0] = 1;

	for (int i = 1; i < sequenceLength; i++) {
		max = 0;
		for (int j = 0; j < i; j++) {
			count++;
			if (sequence[j] < sequence[i] && dp[j] > max)
				max = dp[j];
		}
		dp[i] = 1 + max;
	}

	max = dp[0];
	for (int i = 1; i < sequenceLength; i++) {
		if (dp[i] > max)
			max = dp[i];
	}

	return max;
}

void generateSequence(int size) {
	srand(0);
	int r;
	for (int i = 0; i < size; i++) {
		sequence[i] = rand() % 1000000;
	}
}

int main() {
	
	count = 0;
	/*
	freopen("test.txt", "r", stdin);
	
	scanf("%d", &sequenceLength);

	for (int i = 0; i < sequenceLength; i++) {
		scanf("%d", &sequence[i]);
	}
	*/
	sequenceLength = 1000000;
	generateSequence(sequenceLength);

	printf("%d\n", lis(sequenceLength));
	//printf("%d\n", lisBU());
	printf("%d\n", count);

	return 0;
}