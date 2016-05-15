#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int sequenceLength;
int sequence[N];
int LIS[N];

int l(int n) {
	if (LIS[n])
		return LIS[n];

	int max = 0, tmpMax;

	for (int i = 0; i < n; i++) {
		if (sequence[i] < sequence[n]) {
			tmpMax = l(i);
			if (tmpMax > max)
				max = tmpMax;
		}
	}

	return LIS[n] = 1+max;
}

int lis() {
	int max = LIS[0] = 1;
	int tmpMax;

	for (int i = 1; i < sequenceLength; i++) {
		tmpMax = l(i);
		if (tmpMax > max)
			max = tmpMax;
	}

	return max;
}

int main() {
	scanf("%d", &sequenceLength);

	for (int i = 0; i < sequenceLength; i++) {
		scanf("%d", &sequence[i]);
	}

	printf("%d\n", lis());

	return 0;
}