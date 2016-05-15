/*
* Week 8, LPA course's Problem (Articulation Points)
* University of Coimbra, 12.05.2016
* Author: Artur Pedroso
* License: WTFPL
*/

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <algorithm>

#define N 800

struct Crossing{
    //key: crossingID; value: trafficLoad
    std::map<int, int> connections;
    int parent;
};

Crossing crossings[N+1];
int low[N+1], dfs[N+1], time, maxTraffic;

//O(|E|+|V|) ... O(N^2)
void findMaxTrafficLoad(int v){
    bool is_articulPoint = false;
    low[v] = dfs[v] = time = time+1;
    for(std::map<int, int>::iterator w = crossings[v].connections.begin(); w != crossings[v].connections.end(); w++){
        if(crossings[w->first].parent != v){
            if(dfs[w->first] == -1){
                //w wasn't visited
                crossings[w->first].parent = v;
                findMaxTrafficLoad(w->first);
                low[v] = std::min(low[v], low[w->first]);
                if(!is_articulPoint &&
                   ((dfs[v] == 1 && dfs[w->first]!=2) ||
                    (dfs[v] != 1 && low[w->first] >= dfs[v]))){
                    //if v is root AND have more than one child
                    //OR low[w] >= dfs[v]
                    //...ARTICULATION POINT... just enter here the first time that AP is detected for this v.
                    //printf("AP: %d\n", v);
                    int tmpMax = 0;
                    for(std::map<int, int>::iterator ap = crossings[v].connections.begin(); ap != crossings[v].connections.end(); ap++){
                        tmpMax += ap->second;
                    }
                    maxTraffic = std::max(maxTraffic, tmpMax);

                    is_articulPoint = true;
                }
            }
            else{
                //back edge
                low[v] = std::min(low[v], dfs[w->first]);
            }
        }
    }
}

void printOutput(){
    if(maxTraffic){
        printf("%d\n", maxTraffic);
    }
    else{
        printf("Well designed city!\n");
    }
}

int main()
{
    //freopen("test.txt", "r", stdin);
    int numCrossings, numConnections, crossId, trafficLoad;
    while(scanf("%d", &numCrossings) != EOF){
        for (int i = 1; i <= numCrossings; i++){
            scanf("%d", &numConnections);
            for(int j = 0; j < numConnections; j++){
                scanf("%d %d", &crossId, &trafficLoad);
                crossings[i].connections[crossId] = trafficLoad;
                crossings[i].parent = 0;
            }
        }

        //initialize vars
        time = 0;
        maxTraffic = 0;
        for(int i = 1; i <= numCrossings; i++){
            dfs[i] = -1;
        }

        findMaxTrafficLoad(1);

        printOutput();

        //clear crossing connections
        for(int i = 1; i <= numCrossings; i++){
            crossings[i].connections.clear();
        }
    }

    return 0;
}
