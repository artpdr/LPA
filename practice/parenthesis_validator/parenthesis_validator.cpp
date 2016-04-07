#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool string_validator(string parenthesis_string);

int main(){
	int n_lines;
	string parenthesis_string;
	string n_lines_input;

	getline(cin, n_lines_input);

	stringstream(n_lines_input) >> n_lines;

	while(n_lines--){
		getline(cin, parenthesis_string);
		if(string_validator(parenthesis_string))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}


bool string_validator(string parenthesis_string){
	char opened_parenthesis [128];
	int last_opened_index = 0;
	int string_size = parenthesis_string.size();

	for (int i = 0; i < string_size; i++){
		if(parenthesis_string[i] == '(' || parenthesis_string[i] == '[')
			opened_parenthesis[last_opened_index++] = parenthesis_string[i];
		else{
			last_opened_index--;
			if(last_opened_index < 0)
				return false;
			if((parenthesis_string[i] == ')' && opened_parenthesis[last_opened_index] != '(') ||
			   (parenthesis_string[i] == ']' && opened_parenthesis[last_opened_index] != '['))
				return false;
		}
	}

	if(last_opened_index == 0)
		return true;

	return false;
}
