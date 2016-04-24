/*
* Week 6, LPA course's Problem
* University of Coimbra, 21.04.2016
* Author: Artur Pedroso
* License: WTFPL
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#define K 6
#define N 25

struct Team {
	char members[K+1]; //index of members presented in the Team/Group including the leader
	double fitness[128]; //2^(K+1)
};

Team teams[N];
double max_fit_wo_restrictions[N][128][K + 2];
double best;
int n, k;
//int count;

//best without bit restritions
double upper_bound(char S[], char bit) {
	double this_fitness = 0;
	double tmp_this_fitness_max;
	short int fitness_indx;
	short int increment_fitness_index_exponent;

	for (int i = 0; i < n; i++) {

		fitness_indx = 0;
		increment_fitness_index_exponent = 0;

		int j;
		for (j = 0; j <= k; j++) {
			if (teams[i].members[j] >= bit) {
				increment_fitness_index_exponent = k + 1 - j; //raising 2 to this exponent will give the increment to find the best bound
				fitness_indx += S[(int)teams[i].members[j]] << (k - j);
				break;
			}
		}

		for (j = j+1; j <= k; j++) {
			fitness_indx += S[(int)teams[i].members[j]] << (k - j);
		}

		tmp_this_fitness_max = 0;
		//check if max fitness for this fitness_index with this increment is already calculated
		if (max_fit_wo_restrictions[i][fitness_indx][increment_fitness_index_exponent]) {
			tmp_this_fitness_max = max_fit_wo_restrictions[i][fitness_indx][increment_fitness_index_exponent];
		}
		else {
			double tmp_inc = pow(2, increment_fitness_index_exponent);
			double max_fit_index = pow(2, k + 1);
			for (j = fitness_indx; j < max_fit_index; j += tmp_inc) {
				if (teams[i].fitness[j] > tmp_this_fitness_max)
					tmp_this_fitness_max = teams[i].fitness[j];
			}
			max_fit_wo_restrictions[i][fitness_indx][increment_fitness_index_exponent] = tmp_this_fitness_max;
		}
		
		this_fitness += tmp_this_fitness_max;

	}

	return this_fitness;
}

double fitness(char S[]) {
	double this_fitness = 0;
	int fitness_indx;

	for (int i = 0; i < n; i++) {
		
		fitness_indx = 0;

		for (int j = 0; j <= k; j++) 
			fitness_indx += S[(int)teams[i].members[j]] << (k - j);
		
		this_fitness += teams[i].fitness[fitness_indx];
	
	}

	return this_fitness;
}

void max_fitness(char S[], char bit) {
	//count++;
	if (bit == 0) {
		double maybe_best = fitness(S);
		if (maybe_best > best)
			best = maybe_best;

		S[(int)bit] = 1;
		maybe_best = fitness(S);
		S[(int)bit] = 0;
		if (maybe_best > best)
			best = maybe_best;

		return;
	}

	max_fitness(S, bit - 1);

	S[(int)bit] = 1;
	
	if (bit < n/2 && upper_bound(S, bit) <= best) {
		S[(int)bit] = 0;
		return;
	}

	max_fitness(S, bit - 1);

	S[(int)bit] = 0;
	
}

int main() {
	//freopen("test.txt", "r", stdin);
	int tmp_member;
	char sequence[N];
	
	scanf("%d %d", &n, &k);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= k; j++) {
			scanf("%d", &tmp_member);
			teams[i].members[j] = tmp_member;
		}
		sequence[i] = 0;
	}
		
	int num_fitness_values = pow(2, k+1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < num_fitness_values; j++)
			scanf("%lf", &teams[i].fitness[j]);
	}

	//count = 0;

	best = 0;
		
	max_fitness(sequence, n - 1);
		
	printf("%.6lf\n", best);

	//printf("Num calls: %d\n", count);
	

	return 0;
}