//============================================================================
// Name        : cabbages.cpp
// Author      : Artur Pedroso
// Version     : 1.0
// Copyright   : WTFPL
// Description : My solution for B - cabbages's problem
//============================================================================

#include <iostream>
#include <cstdlib>

int order_scores(int scores[2][5], int len_scores);
void number_of_paths_between_two_scores(int score_a_current, int score_b_current,
										int score_a_goal, int score_b_goal,
										int** dynamic_calcs);


int main() {
	int num_test_cases;
	int num_scores;
	long int curr_paths;
	int scores[2][5];
	int i;
	int max_score_a, max_score_b;
	int** dont_do_unnecessary_calcs_matrix;

	std::cin >> num_test_cases;
	while(num_test_cases--){
		i=0;
		std::cin >> num_scores;
		while(i < num_scores){
			std::cin >> scores[0][i];
			std::cin >> scores[1][i];
			i++;
		}
		if(order_scores(scores, num_scores) == 0){
			i = 0;

			//alloc memory for dynamic matrix
			dont_do_unnecessary_calcs_matrix = (int**) std::calloc(scores[0][i]+1, sizeof(int*));
			for(int j = 0; j < scores[0][i]+1; j++){
				dont_do_unnecessary_calcs_matrix[j] = (int*) std::calloc(scores[1][i]+1, sizeof(int));
			}
			if (dont_do_unnecessary_calcs_matrix == NULL || *dont_do_unnecessary_calcs_matrix == NULL){
				return -1;
			}

			number_of_paths_between_two_scores(0, 0, scores[0][i], scores[1][i], dont_do_unnecessary_calcs_matrix);
			curr_paths = dont_do_unnecessary_calcs_matrix[0][0];

			//free memory
			for(int j = 0; j < scores[0][i]+1; j++){
				std::free(dont_do_unnecessary_calcs_matrix[j]);
			}
			std::free(dont_do_unnecessary_calcs_matrix);

			i++;
			while(i < num_scores){
				max_score_a = scores[0][i] - scores[0][i-1];
				max_score_b = scores[1][i] - scores[1][i-1];

				//alloc memory for dynamic matrix
				dont_do_unnecessary_calcs_matrix = (int**) std::calloc(max_score_a+1, sizeof(int*));
				for(int j = 0; j < max_score_a+1; j++){
					dont_do_unnecessary_calcs_matrix[j] = (int*) std::calloc(max_score_b+1, sizeof(int));
				}
				if (dont_do_unnecessary_calcs_matrix == NULL || *dont_do_unnecessary_calcs_matrix == NULL){
					return -1;
				}

				number_of_paths_between_two_scores(0, 0, max_score_a, max_score_b, dont_do_unnecessary_calcs_matrix);
				curr_paths *= dont_do_unnecessary_calcs_matrix[0][0];

				//free memory
				for(int j = 0; j < max_score_a+1; j++){
					std::free(dont_do_unnecessary_calcs_matrix[j]);
				}
				std::free(dont_do_unnecessary_calcs_matrix);

				i++;
			}
			std::cout << curr_paths << std::endl;
		}
		else{
			std::cout << -1 << std::endl;
		}
	}
	return 0;
}


/*align vector of scores
**return 0 if aligned correctly or -1 if there is an inconsistency*/
int order_scores(int scores[2][5], int len_scores){
	int current_val_a, current_val_b, pos_anterior;
	for(int i = 1; i < len_scores; i++){
		current_val_a = scores[0][i];
		current_val_b = scores[1][i];
		pos_anterior = i-1;
		while(pos_anterior > -1 && scores[0][pos_anterior] >= current_val_a){
			if(scores[0][pos_anterior] == current_val_a){
				if (scores[1][pos_anterior] > current_val_b){
					scores[0][pos_anterior+1] = scores[0][pos_anterior];
					scores[1][pos_anterior+1] = scores[1][pos_anterior];
					pos_anterior--;
				}
				else{
					break;
				}
			}
			else{
				scores[0][pos_anterior+1] = scores[0][pos_anterior];
				scores[1][pos_anterior+1] = scores[1][pos_anterior];
				pos_anterior--;
			}
		}
		scores[0][pos_anterior+1] = current_val_a;
		scores[1][pos_anterior+1] = current_val_b;
	}

	//verify if there is any inconsistency undetected before
	for(int i = 0; i < len_scores-1; i++){
		if(scores[1][i] > scores[1][i+1]){
			return -1;
		}
	}

	return 0;
}

/**
 * find number of paths between two scores
 */
void number_of_paths_between_two_scores(int score_a_current, int score_b_current,
										int score_a_goal, int score_b_goal,
										int** dynamic_calcs){

	if(score_a_current+1 > score_a_goal || score_b_current+1 > score_b_goal){
		//in this condition we just have one path to the goal
		dynamic_calcs[score_a_current][score_b_current] = 1;
		return;
	}


	if(	dynamic_calcs[score_a_current+1][score_b_current] > 0 &&
		dynamic_calcs[score_a_current][score_b_current+1] > 0){
		//in this case the sum of the paths is the sum of the paths that are possible
		//if player A get the point or if player B get the point.
		dynamic_calcs[score_a_current][score_b_current] = dynamic_calcs[score_a_current+1][score_b_current]
														+ dynamic_calcs[score_a_current][score_b_current+1];
		return;
	}

	number_of_paths_between_two_scores(	score_a_current+1, score_b_current,
										score_a_goal, score_b_goal, dynamic_calcs);

	number_of_paths_between_two_scores(	score_a_current, score_b_current+1,
										score_a_goal, score_b_goal, dynamic_calcs);

	//in this case the sum of the paths is the sum of the paths that are possible
	//if player A get the point or if player B get the point.
	dynamic_calcs[score_a_current][score_b_current] = dynamic_calcs[score_a_current+1][score_b_current]
													+ dynamic_calcs[score_a_current][score_b_current+1];
	return;

}
