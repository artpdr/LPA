/*#include "stdafx.h"*/
#include <iostream>
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
	
	while (std::cin >> n_homeworks_) {
		
		for (int i = 0; i < n_homeworks_; i++) {
			std::cin >> homework_[i].working_num_days >> homework_[i].deadline;
		}

		std::cin >> start_day_;

		std::sort(homework_, homework_+n_homeworks_, customComparator);

		major_gap_ = 0;
		greedy_min_max_gap();

		std::cout << major_gap_ << std::endl;

	}

    return 0;
}

