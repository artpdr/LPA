#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1024

char m_[MAX_SIZE][MAX_SIZE];
int i_, j_;
void pavements(int n, int r);
void print_pavement(int n);

int main(){
	int N, R;
	char tmp_char;
	do{
		scanf("%d %d", &N,&R);
		do{
			tmp_char = getchar();
		}while(tmp_char != EOF && tmp_char!='\n');
		pavements(N, R);
		print_pavement(N);
	}while(tmp_char != EOF);
	return 0;
}


void pavements(int n, int r){
	int two_to_the_n, two_to_the_n_minus_one, half_two_to_the_n, rotations;
	char tmp_color;
	if (n == 0){
		m_[0][0] = 0;
		return;
	}
	pavements(n-1, r);

	two_to_the_n = pow(2, n);
	two_to_the_n_minus_one = pow(2, n-1);
	half_two_to_the_n = two_to_the_n/2;

	rotations = r%4;

	for(i_ = 0; i_ < two_to_the_n; i_++){
		for(j_ = 0; j_ < two_to_the_n; j_++){
			if (i_ >= half_two_to_the_n && j_ >= half_two_to_the_n){
				m_[i_][j_] = !m_[i_ % two_to_the_n_minus_one][j_ % two_to_the_n_minus_one];
				if(rotations > 0){
					if(rotations == 1){
						tmp_color = m_[i_ - half_two_to_the_n][j_];
						m_[i_ - half_two_to_the_n][j_] = m_[i_][j_];
						m_[i_][j_] = tmp_color;
					}
					else if(rotations == 2){
						tmp_color = m_[i_ - half_two_to_the_n][j_ - half_two_to_the_n];
						m_[i_ - half_two_to_the_n][j_ - half_two_to_the_n] = m_[i_][j_];
						m_[i_][j_] = tmp_color;
					}
					else if(rotations == 3){
						tmp_color = m_[i_][j_ - half_two_to_the_n];
						m_[i_][j_ - half_two_to_the_n] = m_[i_][j_];
						m_[i_][j_] = tmp_color;
					}
				}
			}
			else{
				m_[i_][j_] = m_[i_ % two_to_the_n_minus_one][j_ % two_to_the_n_minus_one];	
			}
		}
	}
}

void print_pavement(int n){
	int two_to_the_n = pow(2, n);
	for(i_ = 0; i_ < two_to_the_n; i_++){
		for(j_ = 0; j_ < two_to_the_n; j_++){
			printf("%d", m_[i_][j_]);
		}
		printf("\n");
	}
}