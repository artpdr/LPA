#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#define N 5000

int n; //numero de elemento na sequencia
int sequence[N]; //elementos da sequencia
int lis_dp[N];//auxiliary dynamic programming matrix for LIS
int lds_dp[N];//auxiliary dynamic programming matrix for LDS
int max_size; //gintonic sequence with max size

//put zeros in dp vectors
void zero_dp_vectors(){
    for (int i = 0; i < n; i++){
        lis_dp[i] = 0;
        lds_dp[i] = 0;
    }
}

//return longest increasing sequence in [s,n[
void LIS(int s, int n){
    //Ver slides
    int m = 0;
    lis_dp[s] = 1;
    for(int i = s+1; i < n; i++){
        m = 0;
        for(int j = 0; j < i; j++){
            if(sequence[j] < sequence[i] && lis_dp[j] > m){
                m = lis_dp[j];
            }
        }
        lis_dp[i] = m+1;
    }

    //coloca o  numero maximo de elementos em sequencia crescente ate a posicao i
    m = 0;
    for(int i = s; i < n; i++){
        if(lis_dp[i] > m){
            m = lis_dp[i];
        }
        else{
            lis_dp[i] = m;
        }
    }
}

//return longest decreasing sequence in [s,n[
void LDS(int s, int n){
    //alteracao a anterior (faz no sentido inverso)
    int m = 0;
    lds_dp[n-1] = 1;
    for(int i = n-2; i >= s; i--){
        m = 0;
        for(int j = n-1; j > i; j--){
            if(sequence[j] < sequence[i] && lds_dp[j] > m){
                m = lds_dp[j];
            }
        }
        lds_dp[i] = m+1;
    }

    //coloca o numero maximo de elementos em sequencia decrescente desde n ate a posicao i
    m = 0;
    for(int i = n-1; i >= s; i--){
        if(lds_dp[i] > m){
            m = lds_dp[i];
        }
        else{
            lds_dp[i] = m;
        }
    }
}

void runAlgorithm(){
    max_size = 0;
    //computa matrizes de programacao dinamica
    LIS(0, n);
    LDS(0, n);
    for(int i = 0; i < n-1; i++){
        max_size = std::max(max_size, lis_dp[i] + lds_dp[i+1]);
    }
}

void printOutput(){
    printf("%d\n", max_size);
}

void readInput(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &sequence[i]);
    }
}

int main()
{
    int num_tests;
    scanf("%d", &num_tests);

    while(num_tests--){
        readInput();
        runAlgorithm();
        printOutput();
        zero_dp_vectors();
    }

    return 0;
}
