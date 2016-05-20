#include <stdlib.h>
#include <stdio.h>

#define N 40

char markedA[N+1];
char marked[N+1];
int nodes[N+1][N+1];
int numNodes;
int best;

void longestPath(int v, int len, int visited){
    if(visited == numNodes/2+1){
        if (len > best){
            best = len;
            for(int i = 1; i <= numNodes; i++){
                markedA[i] = marked[i];
            }
        }
        return;
    }

    for(int i = v+1; i <= numNodes; i++){
        if(!marked[i]){
            marked[i] = 1;
            longestPath(i, len+nodes[v][i], visited+1);
            marked[i] = 0;
        }
    }
}

int main()
{
    freopen("test.txt", "r", stdin);
    scanf("%d", &numNodes);
    int idA, idB, dist;
    for(int i = 0; i < (numNodes*numNodes-numNodes)/2; i++){
        scanf("%d %d %d", &idA, &idB, &dist);
        nodes[idA][idB] = dist;
    }

    best = 0;
    longestPath(1, 0, 1);
    int previous = 1;
    for(int i = 2; i <= numNodes; i++){
        if(!markedA[i]){
            best += nodes[previous][i];
            previous = i;
        }
    }

    printf("%d\n", best);

    return 0;
}
