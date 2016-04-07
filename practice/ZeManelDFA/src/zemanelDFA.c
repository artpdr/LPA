#include <stdio.h>
#include <stdlib.h>
#define M 31
#define N 30

void DFA_moves(char curr_node, char n_moves);

char final_states_[N];
char transitions_[N][2];
char dp[N][2];
unsigned int n_paths_;
int max_moves_;

int main(){
    int n_states, i, move_0, move_1;
    char test_char;
    while(scanf("%d %d", &n_states, &max_moves_) != EOF){
        while(getchar()!='\n');
        i=0;
        while(i < n_states){
            scanf("%d %d", &move_0, &move_1);
            transitions_[i][0] = move_0-1;
            transitions_[i][1] = move_1-1;
            final_states_[i] = 0;
            test_char = getchar();
            while(test_char != '\n' && test_char!=EOF){
                if (test_char == '*'){
                    final_states_[i] = 1;
                }
                test_char = getchar();
            }
            i++;
        }
        n_paths_ = 0;
        DFA_moves(0, 0);
        printf("%u\n", n_paths_);
    }
    return 0;
}

void DFA_moves(char curr_node, char n_moves){
    if(n_moves == max_moves_)
    {
        if(final_states_[(int)curr_node])
            n_paths_++;
        return;
    }

    n_moves++;
    
    DFA_moves(transitions_[(int)curr_node][0], n_moves);
    DFA_moves(transitions_[(int)curr_node][1], n_moves);

    
}