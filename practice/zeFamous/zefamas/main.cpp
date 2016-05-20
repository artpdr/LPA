#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define N 250000

struct Fan{
    int id;
    int day;
    int points;
};

Fan fans[N];
int numFans;
char fansSelected[N+1]; //fans that will have a meeting
char daysReserved[N+1]; //days already taken by a meeting

bool orderByPoints(Fan a, Fan b){
    return a.points > b.points;
}

void greedy(){
    int totalPoints;
    int maxDayReserved = 0;
    bool canReserve;

    if(numFans == 1){
        printf("%d\n", fans[0].id);
        printf("%d\n", fans[0].points);
        return;
    }

    daysReserved[fans[0].day] = 1;
    fansSelected[fans[0].id] = 1;
    totalPoints = fans[0].points;

    for(int i = 1; i < numFans; i++){
        if(maxDayReserved < fans[i].day){
            canReserve = false;
            for(int j = fans[i].day; j > 0; j--){
                if(!daysReserved[j]){
                    canReserve = true;
                    daysReserved[j]=1;
                    fansSelected[fans[i].id] = 1;
                    totalPoints += fans[i].points;
                    break;
                }
            }

            if(!canReserve)
                maxDayReserved = fans[i].day;
        }
    }

    //print id of friends in increasing order
    numFans++;
    for(int i = 1; i < numFans; i++){
        if(fansSelected[i])
            printf("%d\n", i);
    }

    printf("%d\n", totalPoints);
}

int main()
{
    scanf("%d", &numFans);
    for(int i = 0; i < numFans; i++){
        scanf("%d %d %d", &fans[i].id, &fans[i].day, &fans[i].points);
    }

    std::stable_sort(fans, fans+numFans, orderByPoints);

    greedy();

    return 0;
}
