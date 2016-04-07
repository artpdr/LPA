#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_PLACES 12

double distance_[MAX_PLACES][MAX_PLACES];
double minor_distance_;
int num_places_;
char visited[MAX_PLACES];

void set_distance_between_places(int coordinates[2][MAX_PLACES]);
void calc_minor_distance_path(int place, double distance, int num_visited);
void reject_chars();

int main(){
	int i;
	int coordinates[2][MAX_PLACES];
	minor_distance_ = 0;
	scanf("%d", &num_places_);
	reject_chars();
	i=0;
	while(i<num_places_){
		scanf("%d %d", &coordinates[0][i], &coordinates[1][i]);
		reject_chars();
		i++;
	}
	set_distance_between_places(coordinates);
	
	memset(visited, 0, MAX_PLACES*sizeof(char));
	for(i = 0; i < num_places_; i++){
		visited[i] = 1;
		calc_minor_distance_path(i, 0, 1);
		visited[i] = 0;	
	}
	
	
	printf("%.3lf\n", minor_distance_);
	return 0;
}

void reject_chars(){
	char tmp_char;
	do{
		tmp_char = getchar();
	}while (tmp_char != '\n' && tmp_char != EOF);
}

void set_distance_between_places(int coordinates[2][MAX_PLACES]){
	int i, j;
	double dx, dy;

	for(i = 0; i < num_places_; i++){
		distance_[i][i]=0;
		for(j = i+1; j < num_places_; j++){
			dx = pow((coordinates[0][i] - coordinates[0][j]), 2);
			dy = pow((coordinates[1][i] - coordinates[1][j]), 2);
			distance_[i][j] = distance_[j][i] = sqrt(dx+dy);
			minor_distance_+= distance_[i][j];
		}
	}
}

void calc_minor_distance_path(int place, double distance, int num_visited){
	int i;
	if(distance >= minor_distance_)
		return;
	if(num_visited == num_places_){
		if (distance < minor_distance_)
			minor_distance_ = distance;
		return;
	}
	for(i = 0; i < num_places_; i++){
		if(!visited[i] && distance_[i][place]){
			visited[i]=1;
			calc_minor_distance_path(i, distance+distance_[i][place], num_visited+1);
			visited[i]=0;
		}
	}
}