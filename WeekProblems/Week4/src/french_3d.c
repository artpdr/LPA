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
char checked_[501];
int max_hours_, max_ppl_;
int max_prof = 0;
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

		for (j = max_hours_-1; j > 0; j--){
			sum_prof = prof_[1][j] + calc_max(1, j);
			if(sum_prof > max_prof){
				max_prof = sum_prof;
			}
		}

		for(i = 2; i <= max_ppl_; i++){
			sum_prof = prof_[i][1] + calc_max(i, 1);
			if (sum_prof < prof_[i][max_hours_]){
				sum_prof = prof_[i][max_hours_];
			}
			if(sum_prof > max_prof)
				max_prof = sum_prof;
		}	
	

	/*for(i = 1; i <= max_ppl_; i++){
		for(j = 1; j <= max_hours_; j++){
			printf("%3d ", aux_[i][j]);
		}
		printf("\n");
	}*/

	printf("%d\n", max_prof);

	return 0;	
}

/**
* person that we sum before
* hours already taken
* checked nodes(people)
*/
int calc_max(int person, int hours){
	int i, j;
	for(i = 1; i <= max_ppl_; i++){
		for(j = 1; j <= max_hours_; j++){
			
		}
	}
}

