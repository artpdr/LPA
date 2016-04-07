#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

bool test_case (vector<int> men, vector<int> women);

int main(){
	int n_inputs, input;
	vector<int> men;
	vector<int> women;

	cin >> n_inputs;

	do{
		while(n_inputs--){
			cin >> input;
			if(input < 0)
				men.push_back(-input);
			else if (input > 0)
				women.push_back(input);
		}

		cin >> n_inputs;

		if(n_inputs == 0){

			sort(men.begin(), men.end());
			sort(women.begin(), women.end());

			if(test_case(men, women)){
				cout << "Fair" << endl;
			}
			else{
				cout << "Rigged" << endl;
			}
			women.clear();
			men.clear();
		}

		cin >> n_inputs;
	}while(n_inputs);

	return 0;
}


bool test_case (vector<int> men, vector<int> women){
	std::vector<int>::size_type men_vector_sz = men.size();
	std::vector<int>::size_type women_vector_sz = women.size();
	int left, right, sum;

	for (unsigned i = 0; i < men_vector_sz ; i++){
		left = 0; right = women_vector_sz-1;
		if(women[left] < men[i]){
			while(left < right){
				sum = women[left] + women[right];
				if(sum > men[i])
					right--;
				else if(sum < men[i])
					left++;
				else
					return true;
			}
		}
	}

	for (unsigned i = 0; i < women_vector_sz ; i++){
		left = 0; right = men_vector_sz-1;
		if(men[left] < women[i]){
			while(left < right){
				sum = men[left] + men[right];
				if(sum > women[i])
					right--;
				else if(sum < women[i])
					left++;
				else
					return true;
			}
		}
	}

	return false;
}





