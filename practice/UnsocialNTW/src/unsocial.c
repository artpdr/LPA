#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void reject_chars();
void max_size(int p_id, int size, int ** connection, int * neighbour);

int n_memb_, max_size_;

int main(){
	int n_conn, i, p_id1, p_id2;
	int **connection;
	int* neighbour;
	scanf("%d %d", &n_memb_, &n_conn);
	reject_chars();

	connection = (int**) malloc(n_memb_ * sizeof(int*));
	neighbour = (int*) calloc(n_memb_, sizeof(int));
	for(i = 0; i < n_memb_; i++){
		connection[i] = (int *) calloc(n_memb_, sizeof(int));
	}
	/*memory allocation should be verified*/

	i=0;
	while (i < n_conn){
		scanf("%d %d", &p_id1, &p_id2);
		reject_chars();
		connection[p_id1][p_id2]++;
		connection[p_id2][p_id1]++;
		i++;
	}
	max_size_=0;
	max_size(0, 1, connection, neighbour);
	printf("%d\n", max_size_);

	for(i = 0; i < n_memb_; i++){
		free(connection[i]);
	}
	free(connection);
	free(neighbour);
	return 0;
}

void reject_chars(){
	char tmp_char;
	do{
		tmp_char = getchar();
	}while (tmp_char != '\n' && tmp_char != EOF);
}

void max_size(int p_id, int size, int ** connection, int * neighbour){
	int i;
	if(size > max_size_)
		max_size_ = size;
	for(i = p_id + 1; i < n_memb_; i++){
		if(connection[p_id][i])
			neighbour[i]++;
	}
	for(i = p_id + 1; i < n_memb_; i++){
		if(!neighbour[i])
			max_size(i, size+1, connection, neighbour);
	}
	for(i = p_id + 1; i < n_memb_; i++){
		if(connection[p_id][i])
			neighbour[i]--;		
	}
}