#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>

void generate_test_file(FILE *fp, int n, int k){
	srand(0);
	double rand_fitness;
	int rand_elem;
	int elements[7];
	bool already_present;
	fprintf(fp, "%d %d\n", n, k);
	int j;
	for(int i = 0; i < n; i++){
		for(j = 0; j < k; j++){
			rand_elem = rand()%n;
			already_present = false;
			//detect repetitions
			for(int k = 0; k < j; k++){
				if(rand_elem == elements[k] || rand_elem == i){
					j--;
					already_present = true;
					break;
				}
			}
			if(!already_present)
				elements[j] = rand_elem;
		}

		elements[j] = i;
		
		std::sort(elements, elements+k+1);

		for(j = 0; j < k+1; j++){
			fprintf(fp, "%d\n", elements[j]);
		}
	}

	for(int i = 0; i < n; i++){
		for(j = 0; j < pow(2, k+1); j++){
			rand_fitness = (rand()%1001) / 1000.0;
			fprintf(fp, "%.6lf\n", rand_fitness);
		}
	}	
}

int main(int argc, char** argv){
	FILE *fp;
	
	if(argc < 3){
		printf("Run again with parameters n, k\n");
		return -1;
	}

	fp = fopen ("customTest.txt","w");

	if(atoi(argv[2]) > 6 || atoi(argv[2]) < 1){
		printf("Value of k need to be: 0 < k < 7\n");
		return -1;
	}

	if(atoi(argv[1]) > 25 || atoi(argv[1]) < 1 || atoi(argv[1]) <= atoi(argv[2])){
		printf("Value of n need to be: 0 < n < 25 AND n > k \n");
		return -1;
	}

	generate_test_file(fp, atoi(argv[1]), atoi(argv[2]));

	fclose(fp);

	return 0;
}