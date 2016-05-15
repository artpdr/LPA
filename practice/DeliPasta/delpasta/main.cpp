#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

int maxTaste(int **tastes, int **dp, int num_pastas, int time_bound){
    if(dp[num_pastas][time_bound])
        return dp[num_pastas][time_bound];

    if(num_pastas == 1){
        return tastes[num_pastas][time_bound];
    }

    int tmp_max=0, max_local=tastes[num_pastas][time_bound];

    for(int t = 1; t <= time_bound; t++){
        tmp_max = maxTaste(tastes, dp, num_pastas-1, t) + tastes[num_pastas][time_bound-t];
        max_local = std::max(max_local, tmp_max);
    }

    return dp[num_pastas][time_bound] = max_local;
}

int main()
{
    int num_pastas, time_bound, trash;
    int **dp, **tastes;
    scanf("%d %d", &num_pastas, &time_bound);

    dp = (int**) malloc((num_pastas+1) * sizeof(int*)); //used for dynamic programming
    tastes = (int**) malloc((num_pastas+1) * sizeof(int*)); // save pastas/time tastes
    for(int i = 0; i <= num_pastas; i++){
        dp[i] = (int *) calloc(time_bound+1, sizeof(int));
        tastes[i] = (int *) calloc(time_bound+1, sizeof(int));
    }

    for(int i = 1; i <= num_pastas; i++){
        for(int j = 1; j <= time_bound; j++){
            scanf("%d %d %d", &trash, &trash, &tastes[i][j]);
        }
    }

    maxTaste(tastes, dp, num_pastas, time_bound);

    printf("%d\n", dp[num_pastas][time_bound]);

    return 0;
}
