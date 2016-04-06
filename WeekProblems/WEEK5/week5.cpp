/*#include "stdafx.h"*/
#include <cstdio>
#include <vector>
#include <algorithm>

struct Homework {
	int working_num_days;
	int deadline;
};

Homework homework_[20000];
int n_homeworks_;
int major_gap_;
int start_day_;

bool customComparator(Homework x, Homework y) {
	return x.deadline < y.deadline;
}

void greedy_min_max_gap() {
	int gap;

	for (int i = 0; i < n_homeworks_; i++) {
		start_day_ += homework_[i].working_num_days;
		gap = start_day_ - homework_[i].deadline;
		
		if (gap > major_gap_)
			major_gap_ = gap;
	}

}

int main()
{
	
	while (scanf("%d", &n_homeworks_)!=EOF) {
		
		for (int i = 0; i < n_homeworks_; i++) {
			scanf("%d", &(homework_[i].working_num_days));
			scanf("%d", &(homework_[i].deadline));
		}

		scanf("%d", &start_day_);

		std::sort(homework_, homework_+n_homeworks_, customComparator);

		major_gap_ = 0;
		greedy_min_max_gap();

		printf("%d\n", major_gap_);

	}

    return 0;
}

