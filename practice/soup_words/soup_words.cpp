#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

void order_chaos(vector<string> words, int n_words, int sz_word);

int main(){
  int n_words, sz_word;
  string tmp;
  vector<string> words;

  while(cin >> n_words >> sz_word){
	words.clear();
	for (int i = 0; i < n_words; i++){
	  cin >> tmp;
	  words.push_back(tmp);
	}
	order_chaos(words, n_words, sz_word);
  }

  return 0;
}

void order_chaos(vector<string> words, int n_words, int sz_word){
  string original_word = words[0];
  int vector_letters_changed[n_words];
  int letters_changed, current_character;
  vector_letters_changed[0] = 0;
  for (int i = 1; i < n_words; i++){
    letters_changed = 0;
    for(current_character = 0; current_character < sz_word; current_character++){
      if(words[i][current_character] != original_word[current_character])
        letters_changed++;
    }
    vector_letters_changed[letters_changed] = i;
  }

  for (int i = 0; i < n_words; i++){
    cout << words[vector_letters_changed[i]] << endl;
  }
}
