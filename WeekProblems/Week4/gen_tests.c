#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
	int i, j, num_people, num_hours, prof;
	FILE * pFile;
	srand(time(NULL));
	if (argc != 3){
		printf ("Run as gen_tests <num_people> <num_hours>\n");
		return -1;
	}


	pFile = fopen ("generated_test.txt","w");
	if (pFile==NULL)
	{
		printf("Can't write on file generated_test.txt\n");
		return -1;		
	}

	num_people = atoi(argv[1]);
	num_hours = atoi(argv[2]);
	fprintf(pFile, "%d %d \n", num_hours, num_people);

	for (i = 1; i <= num_people; i++){
		for(j = 1; j <= num_hours; j++){
			prof = ((j-1)*10) + 1 + rand()%10;
			fprintf(pFile, "%d %d %d\n", i, j, prof);
		}
	}

	fclose (pFile);
	return 0;
}