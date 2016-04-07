/**
*My solution for scheduling n jobs with same priority in m processors
*with the shortest possible time. For LPA course in University of Coimbra
*Author: Artur Pedroso
*Date: 04-03-2016
*Licence: WTFPL 
*/

#include <stdlib.h>
#include <stdio.h>
#define JOBS_MAX 30
#define PROCESSORS_MAX 15

int _processors_time[PROCESSORS_MAX], _times_proc_jobs[PROCESSORS_MAX][JOBS_MAX], aux[PROCESSORS_MAX][JOBS_MAX];
int _best;
int _num_jobs, _num_processors;
int _sum_processors_times;
int counter = 0;

void find_greedy_best();
void find_best_of_best(int job_number, int proc_num, int actual_time);


int main(int argc, char **argv){
	int i,j;
	_best = 0;

	scanf("%d", &_num_jobs);
	scanf("%d", &_num_processors);

	for(i = 0; i < _num_processors; i++){
		_processors_time[i] = 0;
	}

	i=0;
	while(i < _num_processors){
		j=0;
		while(j < _num_jobs){
			scanf("%d", &(_times_proc_jobs[i][j]));
			j++;
		}
		i++;
	}

	find_greedy_best();

	find_best_of_best(0, 0, 0);

	printf("%d\n", _best);

	return 0;

}


void find_greedy_best(){
	int i, j, processor_with_min_time, min_time;

	for (j = 0; j < _num_jobs; j++){
		processor_with_min_time = 0;
		min_time = _processors_time[processor_with_min_time] + _times_proc_jobs[processor_with_min_time][j];
		for(i = 1; i < _num_processors; i++){
			if (_processors_time[i] + _times_proc_jobs[i][j] < min_time){
				processor_with_min_time = i;
				min_time = _processors_time[i] + _times_proc_jobs[i][j];
			}
		}
		_processors_time[processor_with_min_time] = min_time;
	}

	_best = _processors_time[0];
	for(i = 1; i < _num_processors; i++){
		if(_processors_time[i] > _best)
			_best = _processors_time[i];
	}

	for(i = 0; i < _num_processors; i++){
		_processors_time[i] = 0;
	}
}


void find_best_of_best(int job_number, int proc_num, int actual_time){
	int i, min_time_in_processor;

	if(actual_time >= _best){
		return;
	}

	if (job_number == _num_jobs){
		_best = actual_time;
		return;
	}

	min_time_in_processor = _times_proc_jobs[0][job_number];
	
	for(i = 0; i < _num_processors; i++){
		if(aux[i][job_number] > 0){
			printf("smt\n");
			if(_processors_time[i] + aux[i][job_number] < _best){
				_best = _processors_time[i] + aux[i][job_number];
			}
			return;
		}
		_processors_time[i] += _times_proc_jobs[i][job_number];
		if(_processors_time[i] > actual_time)
			find_best_of_best(job_number+1, i, _processors_time[i]);
		else
			find_best_of_best(job_number+1, i, actual_time);
		_processors_time[i] = 0;
		
		if(min_time_in_processor > _times_proc_jobs[i][job_number]){
			min_time_in_processor = _times_proc_jobs[i][job_number];
		}
	}

	if(job_number < _num_jobs-1){
		counter++;
		printf("%d\n", counter);
		aux[proc_num][job_number] += aux[proc_num][job_number+1];
	}
	else{
		aux[proc_num][job_number] += _times_proc_jobs[proc_num][job_number];	
	}
}