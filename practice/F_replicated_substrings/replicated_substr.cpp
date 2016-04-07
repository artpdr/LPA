#include <iostream>
#include <string>
using namespace std;

int count_minor_substr(string s);
bool is_substr(string s, int left, int substr_length, int maxsize);


int main(){
  string input_string;
  int inputs_num;

  cin >> inputs_num;
  inputs_num--;
  while(inputs_num --){
	  cin >> input_string;

	  cout << count_minor_substr(input_string) << endl << endl;
  }

  cin >> input_string;

  cout << count_minor_substr(input_string) << endl;


  return 0;
}

int count_minor_substr(string s){
	int s_len = s.size();
	for(int i = 1; i < s_len; i++){
		if (s[0] == s[i]){
			if(s_len % (i) == 0){
				if (is_substr(s, 0, i, s_len)){
					return i;
				}
			}
		}
	}
	return s_len;
}

bool is_substr(string s, int left, int substr_length, int maxsize){
	if(left + substr_length < maxsize){
		if(s.substr(left, substr_length).compare(s.substr(left+substr_length, substr_length))){
			return false;
		}
		return is_substr(s, left+substr_length, substr_length, maxsize);
	}
	return true;
}
