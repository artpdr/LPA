#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

char M_[100][100];
char path_[100][100];
int rows_, cols_;

int try_path(char sign, int r, int c, int last_col);

int main(){
	int i, j;
	int found;

	while(scanf("%d %d", &rows_, &cols_) != EOF){
		while(getchar() != '\n');
		for(i = 0; i < rows_; i++){
			for(j = 0; j < cols_; j++){
				scanf("%c", &(M_[i][j]));
			}
			while(getchar() != '\n');
		}
		found = false;
		for(i = 0; i < rows_; i++){
			memset(path_[i], 0, 100*sizeof(char));
		}
		for(i = 0; i < cols_; i++){
			if(M_[rows_-1][i] != '#'){
				if(rows_-1 == 0){
					printf("(%d,%d)\n", rows_, i+1);
					found = true;
					break;
				}
				if (try_path(M_[rows_-1][i], rows_-1, i, i)){
					printf("(%d,%d)\n", rows_, i+1);
					found = true;
					break;
				}
			}
		}
		if (!found)
			printf("No Path!\n");
	}

	return 0;
}


int try_path(char sign, int r, int c, int last_col){
	path_[r][c] = 'X';
	if (sign == '|'){
		if(c-1 > -1 && M_[r-1][c-1] == '\\'){
			if(r-1 == 0){
				printf("(%d,%d),", r, c);
				return true;
			}
			if (path_[r-1][c-1]==0 && try_path('\\', r-1, c-1, c)){
				printf("(%d,%d),", r, c);
				return true;
			}
		}
		if(M_[r-1][c] == '|'){
			if(r-1 == 0){
				printf("(%d,%d),", r, c+1);
				return true;
			}
			if (path_[r-1][c]==0 && try_path('|', r-1, c, c)){
				printf("(%d,%d),", r, c+1);
				return true;
			}
		}
		if(c+1 < cols_ && M_[r-1][c+1] == '/'){
			if(r-1 == 0){
				printf("(%d,%d),", r, c+2);
				return true;
			}
			if (path_[r-1][c+1]==0 && try_path('/', r-1, c+1, c)){
				printf("(%d,%d),", r, c+2);
				return true;
			}
		}
	}
	else if(sign == '/'){
		if(M_[r-1][c] == '\\'){
			if(r-1 == 0){
				printf("(%d,%d),", r, c+1);
				return true;
			}
			if (path_[r-1][c]==0 && try_path('\\', r-1, c, c)){
				printf("(%d,%d),", r, c+1);
				return true;
			}
		}
		if(c+1 < cols_ && M_[r-1][c+1] == '/' && last_col <= c){
			if(r-1 == 0){
				printf("(%d,%d),", r, c+2);
				return true;
			}
			if (path_[r-1][c+1]==0 && try_path('/', r-1, c+1, c)){
				printf("(%d,%d),", r, c+2);
				return true;
			}
		}	
		if(c+1 < cols_ && M_[r-1][c+1] == '|' && last_col <= c){
			if(r-1 == 0){
				printf("(%d,%d),", r, c+2);
				return true;
			}
			if (path_[r-1][c+1]==0 && try_path('|', r-1, c+1, c)){
				printf("(%d,%d),", r, c+2);
				return true;
			}
		}
		if(r < rows_-1 && c+1 < cols_ && M_[r][c+1] == '\\'){
			if (path_[r][c+1] == 0 && try_path('\\', r, c+1, c)){
				printf("(%d,%d),", r+1, c+2);
				return true;
			}
		}
		if(r < rows_-1 && c-1 > -1 && M_[r][c-1] == '\\' && last_col > c){
			if (path_[r][c-1]==0 && try_path('\\', r, c-1, c)){
				printf("(%d,%d),", r+1, c);
				return true;
			}
		}
	}
	else if(sign == '\\'){
		if(M_[r-1][c] == '/'){
			if(r-1 == 0){
				printf("(%d,%d),", r, c+1);
				return true;
			}
			if (path_[r-1][c]==0 && try_path('/', r-1, c, c)){
				printf("(%d,%d),", r, c+1);
				return true;
			}
		}
		if(c-1 > -1 && M_[r-1][c-1] == '\\' && last_col >= c){
			if(r-1 == 0){
				printf("(%d,%d),", r, c);
				return true;
			}
			if (path_[r-1][c-1]==0 && try_path('\\', r-1, c-1, c)){
				printf("(%d,%d),", r, c);
				return true;
			}
		}	
		if(c-1 > -1 && M_[r-1][c-1] == '|' && last_col >= c){
			if(r-1 == 0){
				printf("(%d,%d),", r, c);
				return true;
			}
			if (path_[r-1][c-1]==0 && try_path('|', r-1, c-1, c)){
				printf("(%d,%d),", r, c);
				return true;
			}
		}
		if(r < rows_-1 && c+1 < cols_ && M_[r][c+1] == '/' && last_col < c){
			if (path_[r][c+1]==0 && try_path('/', r, c+1, c)){
				printf("(%d,%d),", r+1, c+2);
				return true;
			}
		}
		if(r < rows_-1 && c-1 > -1 && M_[r][c-1] == '/'){
			if (path_[r][c-1]==0 && try_path('/', r, c-1, c)){
				printf("(%d,%d),", r+1, c);
				return true;
			}
		}
	}	
	return false;
}