/**
* My solution to get the most proeficiency level talking to num_people 
* with a limit of num_hours. For LPA course in University of Coimbra
* Author: Artur Pedroso
* Date: 11-03-2016
* Licence: WTFPL 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int prof_[501][501], aux_[501][501];
int max_hours_, max_ppl_;
int max_prof_ = 0;

int calc_max(int person, int hours);

int main(){
	int i, j;
	int sum_prof;
	int n_peer, n_h_talk, n_prof; 
	while(scanf("%d %d", &max_hours_, &max_ppl_) != EOF){
		for(i = 0; i < max_ppl_*max_hours_; i++){
			scanf("%d %d %d", &n_peer, &n_h_talk, &n_prof);
			prof_[n_peer][n_h_talk] = n_prof;
			aux_[n_peer][n_h_talk] = 0;
			while(getchar() != '\n');
		}
	}


	for (j = max_hours_; j > -1; j--){
		sum_prof = prof_[max_ppl_][j] + calc_max(max_ppl_, max_hours_ - j);
		if(sum_prof > max_prof_){
			max_prof_ = sum_prof;
		}
	}

	printf("%d\n", max_prof);

	return 0;	
}

/**
* person: number of the person that calls
* hours: number of hours that we are searching for max
*/
int calc_max(int person, int hours){
	int j, sum_prof, max_sum=0;
	person--;

	if(aux_[person][hours] > 0){
		return aux_[person][hours];
	}

	if(hours == 0){
		return 0;
	}
	
	if(person == 1){
		return prof_[person][hours];
	}

	for(j = hours; j > -1; j--){
		sum_prof = prof_[person][j] + calc_max(person, hours - j);
		if (sum_prof > max_sum){
			max_sum = sum_prof;
		}
	}
	aux_[person][hours] = max_sum;
	return max_sum;
}

