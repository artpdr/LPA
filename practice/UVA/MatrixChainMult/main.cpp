#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define N 10

struct Matrix{
    int rows;
    int cols;
};

Matrix matrices[N+1];
char kPos[N+1][N+1];
int dp[N+1][N+1];

int minMult(int i, int j){
    if(j <= i)
        return 0;

    if(dp[i][j])
        return dp[i][j];

    int min = INT_MAX, tmpMin;

    for(int k = i; k < j; k++){
        tmpMin =  minMult(i, k) + minMult(k+1, j) + matrices[i].rows * matrices[k].cols * matrices[j].cols;
        if(tmpMin < min){
            min = tmpMin;
            kPos[i][j] = k;
        }
    }

    return dp[i][j] = min;
}

void printParenthesis(int i, int j){
    if(i != j){
        printf("(");
        printParenthesis(i, kPos[i][j]);
        printf(" x ");
        printParenthesis(kPos[i][j]+1, j);
        printf(")");
        return;
    }
    printf("A%d", i);
}

int main()
{
    /*freopen("test.txt", "r", stdin);
    freopen("test_out.txt", "w", stdout);
*/
    int numMatrices;
    int numCase=1;
    while(scanf("%d", &numMatrices) && numMatrices){
        for(int i = 1; i <= numMatrices; i++){
            scanf("%d %d", &matrices[i].rows, &matrices[i].cols);
        }

        memset(kPos, 0, sizeof(kPos));

        for(int i = 1; i <= numMatrices; i++){
            for(int j = 1; j <= numMatrices; j++){
                dp[i][j] = 0;
            }
        }

        minMult(1, numMatrices);

        printf("Case %d: ", numCase++);
        printParenthesis(1, numMatrices);
        printf("\n");
    }
    return 0;
}
