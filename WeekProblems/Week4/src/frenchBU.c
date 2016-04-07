/**
* My solution to get the most proficiency level talking to num_people 
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

void calc_max();

int main(){
	int i;
	int n_peer, n_h_talk, n_prof; 
	while(scanf("%d %d", &max_hours_, &max_ppl_) != EOF){
		for(i = 0; i < max_ppl_*max_hours_; i++){
			scanf("%d %d %d", &n_peer, &n_h_talk, &n_prof);
			prof_[n_peer][n_h_talk] = n_prof;
			aux_[n_peer][n_h_talk] = 0;
			while(getchar() != '\n');
		}
	}


	calc_max();

	/*just decrementing again because they were incremented inside
	**calc_max function to accelerate the calcs*/
	max_hours_--;
	max_ppl_--;
	
	printf("%d\n", aux_[max_ppl_][max_hours_]);

	return 0;	
}


void calc_max(){
	int i,j,k, j_aux, max_prof, max_temp, i_prev;
	/*just to accelerate comparation calcs*/
	max_hours_++;
	max_ppl_++;
	for(j = 1; j < max_hours_; j++){
		aux_[1][j] = prof_[1][j];
		max_prof = aux_[1][j];
		j_aux = j+1;
		for(i = 2; i < max_ppl_; i++){
			i_prev = i-1;
			max_prof = 0;
			for(k = 0; k < j_aux; k++){
				max_temp = prof_[i][k] + aux_[i_prev][j-k];
				if(max_temp > max_prof){
					max_prof = max_temp;
				}
			}
			aux_[i][j] = max_prof;
		}
	}
}

