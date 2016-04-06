/*#include "stdafx.h"*/
#include <iostream>
#include <stdlib.h>
#define MAX_N 7

char border_[MAX_N][MAX_N];
char visited_[MAX_N][MAX_N];
int border_size_;
int best_;
int n_towers_;
void catch_black_towers(int j, int i, int n_moves, int catched) {
	/*char found=0;*/
	if (n_moves >= best_)
		return;
	
	/*if (catched == n_towers_-1) {
		for (int k = 0; k < border_size_ && !found; k++) {
			for (int l = 0; l < border_size_; l++) {
				if (!visited_[k][l] && border_[k][l]) {
					n_moves += abs(i - k) + abs(j - l);
					if (n_moves < best_)
						best_ = n_moves;
					found = 1;
					break;
				}
			}
		}
		return;
	}
	else {*/

	if (catched == n_towers_) {
		if (n_moves < best_)
			best_ = n_moves;
		return;
	}

		if (j + 1 < border_size_ && !visited_[i][j+1]) {
			visited_[i][j + 1] = 1;
			if (border_[i][j + 1]) {
				catch_black_towers(j + 1, i, n_moves + 1, catched + 1);
			}
			else {
				catch_black_towers(j + 1, i, n_moves + 1, catched);
			}
			visited_[i][j + 1] = 0;
		}
		if (j - 1 > -1 && !visited_[i][j - 1]) {
			visited_[i][j - 1] = 1;
			if (border_[i][j - 1]) {
				catch_black_towers(j - 1, i, n_moves + 1, catched + 1);
			}
			else {
				catch_black_towers(j - 1, i, n_moves + 1, catched);
			}
			visited_[i][j - 1] = 0;
		}
		if (i + 1 < border_size_ && !visited_[i+1][j]) {
			visited_[i+1][j] = 1;
			if (border_[i+1][j]) {
				catch_black_towers(j, i+1, n_moves + 1, catched + 1);
			}
			else {
				catch_black_towers(j, i+1, n_moves + 1, catched);
			}
			visited_[i + 1][j] = 0;
		}
		if (i - 1 > -1 && !visited_[i - 1][j]) {
			visited_[i - 1][j] = 1;
			if (border_[i - 1][j]) {
				catch_black_towers(j, i - 1, n_moves + 1, catched + 1);
			}
			else {
				catch_black_towers(j, i - 1, n_moves + 1, catched);
			}
			visited_[i - 1][j] = 0;
		}
	/*} */
}

int main() {
	int n_cases, x_white=0, y_white=0;
	char tmp_c;
	std::cin >> n_cases;
	while (n_cases) {
		n_cases--;
		std::cin >> border_size_;
		n_towers_ = 0;

		for (int i = 0; i < border_size_; i++) {
			for (int j = 0; j < border_size_; j++) {
				std::cin >> tmp_c;
				border_[i][j] = 0;
				visited_[i][j] = 0;
				if (tmp_c == '1') {
					border_[i][j] = tmp_c;
					n_towers_++;
				}
				else if (tmp_c == '2') {
					x_white = j;
					y_white = i;
				}
			}
		}
		
		best_ = border_size_*border_size_;
		if (n_towers_ == best_ - 1) {
			best_--;
		}
		else {
			visited_[y_white][x_white] = 1;
			catch_black_towers(x_white, y_white, 0, 0);
		}
		std::cout << best_ << std::endl;
	}
	return 0;
}
