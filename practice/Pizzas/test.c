#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
	int i;
	float r;
	FILE *fp;
	if(argc < 2){
		printf("run with number of numbers to generate\n");
		return 0;
	}

	srand(0);

	fp = fopen("test.txt", "w");

	int n_vals = atoi(argv[1]);
	fprintf(fp, "%d\n", n_vals);
	for(i=0; i < n_vals; i++){
		r = rand()%1000+1;
		fprintf(fp, "%.2f\n", r);
	}

	fclose(fp);

	return 0;
}