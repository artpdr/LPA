/*Minimum difference problem*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 60

void get_min_diff_time(int time_id, double curr_time);

double times_[N];
int num_times_;
double min_diff_time_;
/*int count_;*/

int main(){
	int i;
	char tmp_char;

	while(scanf("%d", &num_times_)!=EOF){
		i=0;
		min_diff_time_=0;
		while (i < num_times_){
			scanf("%lf", &times_[i]);
			min_diff_time_+=times_[i];
			i++;
			do{
				tmp_char = getchar();
			}while(tmp_char!='\n' && tmp_char != EOF);
		}
		
		/*count_=0;*/
		get_min_diff_time(1, times_[0]);

		printf("%.2lf\n", min_diff_time_);
		/*printf("count_: %d\n", count_);*/
	}

	return 0;
}

void get_min_diff_time(int time_id, double curr_time){
	/*count_++;*/
	if (time_id == num_times_){
		if(fabs(curr_time) < min_diff_time_){
			min_diff_time_ = fabs(curr_time);
		}
		return;
	}

	get_min_diff_time(time_id+1, curr_time + times_[time_id]);
	get_min_diff_time(time_id+1, curr_time - times_[time_id]);
}

