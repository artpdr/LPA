#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 2048


int x_point_,y_point_;
int num_interceptions_;
void reject_chars();
void num_interceptions(int x_center, int y_center, int k);

int main(){
	int size_k;	
	int flag=1;
	while(flag){
		scanf("%d %d %d", &size_k, &x_point_, &y_point_);
		reject_chars();
		if(size_k || x_point_ || y_point_){
			num_interceptions_ = 0;
			num_interceptions(MAXLENGTH/2, MAXLENGTH/2, size_k);
			printf("%3d\n", num_interceptions_);
		}
		else
			flag = 0;
	}
	return 0;
}

void reject_chars(){
	char tmp_char;
	do{
		tmp_char = getchar();
	}while (tmp_char != '\n' );
}

void num_interceptions(int x_center, int y_center, int k){
	int right_margin, left_margin, top_margin, bottom_margin;
	right_margin = x_center+k;
	left_margin = x_center-k;
	bottom_margin = y_center+k;
	top_margin = y_center-k;

	if(	k < 1 || right_margin > MAXLENGTH || left_margin < 0
		|| bottom_margin > MAXLENGTH || top_margin < 0)
		return;

	if(	right_margin >= x_point_ && left_margin <= x_point_ &&
		bottom_margin >= y_point_ && top_margin <= y_point_)
		num_interceptions_++;

	num_interceptions(left_margin, top_margin, k/2);
	num_interceptions(right_margin, top_margin, k/2);
	num_interceptions(right_margin, bottom_margin, k/2);
	num_interceptions(left_margin, bottom_margin, k/2);
}