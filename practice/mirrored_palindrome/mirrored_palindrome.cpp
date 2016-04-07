#include <iostream>
#include <string>

using namespace std;

void test_this_mess(string s, char hash_reverse[]);


int main(){
	string input_string;
	char hash_reverse ['Z'+1];
	for(int i =0; i < (int)('Z'+1); ++i)
		hash_reverse[i] = '\0';

	hash_reverse['A'] = 'A';
	hash_reverse['E'] = '3';
	hash_reverse['H'] = 'H';
	hash_reverse['I'] = 'I';
	hash_reverse['J'] = 'L';
	hash_reverse['L'] = 'J';
	hash_reverse['M'] = 'M';
	hash_reverse['O'] = 'O';
	hash_reverse['S'] = '2';
	hash_reverse['T'] = 'T';
	hash_reverse['U'] = 'U';
	hash_reverse['V'] = 'V';
	hash_reverse['W'] = 'W';
	hash_reverse['X'] = 'X';
	hash_reverse['Y'] = 'Y';
	hash_reverse['Z'] = '5';
	hash_reverse['1'] = '1';
	hash_reverse['2'] = 'S';
	hash_reverse['3'] = 'E';
	hash_reverse['5'] = 'Z';
	hash_reverse['8'] = '8';

	while(getline(cin, input_string) && !input_string.empty()){
		test_this_mess(input_string, hash_reverse);
		cout << endl;
	}

	return 0;
}

void test_this_mess(string s, char hash_reverse[]){
	bool palindrome = true, mirrored = true;
	int left, right, orig_left, orig_right;
	//remove spaces
	left = 0;
	right = s.size()-1;
	while(s[right] == ' ')
		right--;
	while(s[left] == ' ')
		left++;
	orig_left = left;
	orig_right = right;

	while(left <= right && (palindrome || mirrored)){
		if(hash_reverse[(int)s[left]] == '\0' ||
		   hash_reverse[(int)s[left]] != s[right]){
			mirrored = false;
		}
		if(s[left] != s[right]){
			palindrome = false;
		}

		left++; right--;
	}

	if(palindrome && mirrored){
		cout << s.substr(orig_left, orig_right-orig_left+1) << " -- is a mirrored palindrome." << endl;
	}
	else if(palindrome){
		cout << s.substr(orig_left, orig_right-orig_left+1) << " -- is a regular palindrome." << endl;
	}
	else if(mirrored){
		cout << s.substr(orig_left, orig_right-orig_left+1) << " -- is a mirrored string." << endl;
	}
	else{
		cout << s.substr(orig_left, orig_right-orig_left+1) << " -- is not a palindrome." << endl;
	}
}



