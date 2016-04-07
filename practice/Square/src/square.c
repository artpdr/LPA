/*problem where we check if it's possible to construct a square with sticks*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 20
#define true 1
#define false 0
typedef int bool;

bool check_feasible(int stick_number);
int get_square_side(void);
void insertion_sort(void);

int stick_size_[M], basket_sum_[4];
int n_sticks_, square_side_;
/*int count_;*/

int main(){
	int n_cases, i;
	scanf("%d", &n_cases);
	while(getchar()!='\n');
	while(n_cases){
		n_cases--;
		scanf("%d", &n_sticks_);
		i=0;
		while(i<n_sticks_){
			scanf("%d", &stick_size_[i]);
			i++;
		}

		square_side_ = get_square_side();
		if(square_side_){
			/*count_=0;*/
			memset(basket_sum_, 0, 4*sizeof(basket_sum_[0]));
			insertion_sort();
			if (check_feasible(0))
				printf("yes\n");
			else
				printf("no\n");
			/*printf("%d\n", count_);*/
		}
		else
			printf("no\n");

		if(n_cases)
			while(getchar()!='\n');
	}
	return 0;
}

int get_square_side(void){
	int i, sum_sticks_size=0;
	for (i = 0; i < n_sticks_; i++) {
		sum_sticks_size += stick_size_[i];
	}
	if(sum_sticks_size%4==0)
		return sum_sticks_size/4;
	return 0;
}

bool check_feasible(int stick_number){
	/*count_++;*/
	int i, j, feasible;
	if(stick_number == n_sticks_){
		return true;
	}
	for (i = 0 ; i < 4; i++){
		feasible = true;
		for(j=0; j < i; j++){
			if(basket_sum_[j] == basket_sum_[i]){
				feasible=false;
				break;
			}
		}
		if(feasible && (basket_sum_[i]+stick_size_[stick_number] <= square_side_)){
			basket_sum_[i]+=stick_size_[stick_number];
			if(check_feasible(stick_number+1)){
				return true;
			}

			basket_sum_[i]-=stick_size_[stick_number];
		}
	}
	return false;
}

void insertion_sort(void){
	int i, j, choice;
	for(i = 1; i < n_sticks_; i++){
		choice = stick_size_[i];
		j = i-1;
		while(j > -1 && stick_size_[j] < choice){
			stick_size_[j+1] = stick_size_[j];
			j--;
		}
		stick_size_[j+1] = choice;
	}
}