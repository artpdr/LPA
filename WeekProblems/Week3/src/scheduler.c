/**
*My solution for scheduling n jobs with same priority in m processors
*with the shortest possible time. For LPA course in University of Coimbra
*Author: Artur Pedroso
*Date: 04-03-2016
*Licence: WTFPL 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define JOBS_MAX 30
#define PROCESSORS_MAX 15

int _processors_time[PROCESSORS_MAX], _times_proc_jobs[PROCESSORS_MAX][JOBS_MAX], _times_proc_jobs_ordered[PROCESSORS_MAX][JOBS_MAX];
int _best;
int _num_jobs, _num_processors;

void find_greedy_best();
void find_best_of_best(int job_number, int actual_time);


int main(int argc, char **argv){
	int i,j;
	_best = 0;

	scanf("%d", &_num_jobs);
	scanf("%d", &_num_processors);
	
	memset(_processors_time, 0, PROCESSORS_MAX * sizeof(int));

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

	find_best_of_best(0, 0);

	printf("%d\n", _best);

	return 0;

}


/*find greedy best: selecting the job and put in the processor that takes less total time in the current decision
Orders the matrix with processors x job's times (Descending sum of all job time for each processor)*/
void find_greedy_best(){
	int i, j, k, processor_with_min_time, min_time;
	int sums_descending[JOBS_MAX], sum_of_job_time=0, min_sum_pos = 0;
	int temp_pos_sums, job_time_in_processor[PROCESSORS_MAX];

	memset(sums_descending, 0, JOBS_MAX*sizeof(int));
	
	for (j = 0; j < _num_jobs; j++){
		processor_with_min_time = 0;
		min_time = _processors_time[0] + _times_proc_jobs[0][j];
		
		sum_of_job_time = _times_proc_jobs[0][j];
		job_time_in_processor[0] = _times_proc_jobs[0][j];
		
		for(i = 1; i < _num_processors; i++){
			if (_processors_time[i] + _times_proc_jobs[i][j] < min_time){
				processor_with_min_time = i;
				min_time = _processors_time[i] + _times_proc_jobs[i][j];
			}
			
			sum_of_job_time += _times_proc_jobs[i][j];
			job_time_in_processor[i] = _times_proc_jobs[i][j];
		}
		_processors_time[processor_with_min_time] = min_time;


		temp_pos_sums = min_sum_pos;
		while(temp_pos_sums > 0 && sum_of_job_time > sums_descending[temp_pos_sums-1]){
			sums_descending[temp_pos_sums] = sums_descending[temp_pos_sums-1];
			for(k = 0; k < _num_processors; k++){
				_times_proc_jobs_ordered[k][temp_pos_sums] = _times_proc_jobs_ordered[k][temp_pos_sums-1];
			}
			temp_pos_sums--;
		}
			
		sums_descending[temp_pos_sums] = sum_of_job_time;
		for(k = 0; k < _num_processors; k++){
			_times_proc_jobs_ordered[k][temp_pos_sums] = job_time_in_processor[k];
		}
		min_sum_pos++;
	}

	_best = _processors_time[0];
	for(i = 1; i < _num_processors; i++){
		if(_processors_time[i] > _best)
			_best = _processors_time[i];
	}

	memset(_processors_time, 0, PROCESSORS_MAX * sizeof(int));
}


void find_best_of_best(int job_number, int actual_time){
	int i;

	if(actual_time >= _best){
		return;
	}

	if (job_number == _num_jobs){
		_best = actual_time;
		return;
	}
	
	for(i = 0; i < _num_processors; i++){
		_processors_time[i] += _times_proc_jobs_ordered[i][job_number];
		if(_processors_time[i] > actual_time)
			find_best_of_best(job_number+1, _processors_time[i]);
		else
			find_best_of_best(job_number+1, actual_time);
		_processors_time[i] -= _times_proc_jobs_ordered[i][job_number];
	}
}