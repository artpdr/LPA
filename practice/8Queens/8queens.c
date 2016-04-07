#include <stdlib.h>
#include <stdio.h>
int N = 8;
int Q[8];
int nQueens(int col);
int attack(int col);

int main(){
	int i;
	Q[0] = 0;
	nQueens(0);
	for (i = 0; i < N; i++)
		printf("%d ", Q[i]);
	printf("\n");
	return 0;
}

int nQueens(int col){
	int i;
	if(attack(col)){
		return 0;
	}
	if (col == N-1)
		return 1;
	for (i = 1; i < N; i++){
		Q[col+1] = i;
		if(nQueens(col+1))
			return 1;
	}
	return 0;
}

//return true if attack is possible
int attack(int col){
	int i;
	for (i = 0; i < col; i++){
		if(Q[col]==Q[i] || Q[i]==Q[col]-col+i || Q[i]==Q[col]+col-i){
			return 1;
		}
	}	
	return 0;
}