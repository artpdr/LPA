#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define N 600
#define O 250
#define M 1000

unsigned short int dp[N+1][O+1][M+1]; //saves max weight for the restrictions O and M
unsigned short int objects[N][2]; //object's weight and price

unsigned short int findMaxWeight(int numObject, int objectRestriction, int moneyRestriction){
    if(dp[numObject][objectRestriction][moneyRestriction])
        return dp[numObject][objectRestriction][moneyRestriction];

    if(numObject == 0)
        return 0;

    if(objects[numObject][1] > moneyRestriction){
        //we can't keep this
        return dp[numObject][objectRestriction][moneyRestriction] = findMaxWeight(numObject-1, objectRestriction, moneyRestriction);
    }

    if(objectRestriction > 1){
        return dp[numObject][objectRestriction][moneyRestriction] =
        std::max(((short unsigned int)(findMaxWeight(numObject-1, objectRestriction-1, moneyRestriction-objects[numObject][1]) + objects[numObject][0])),
                 findMaxWeight(numObject-1, objectRestriction, moneyRestriction));
    }

    return 0;
}

int main()
{
    int numObjects, objectRestriction, moneyRestriction;
    scanf("%d", &numObjects);
    scanf("%d", &objectRestriction);
    scanf("%d", &moneyRestriction);

    for(int i = 1; i <= numObjects; i++){
        scanf("%hu %hu", &objects[i][0], &objects[i][1]);
    }

    findMaxWeight(numObjects, objectRestriction, moneyRestriction);

    printf("%d\n", dp[numObjects][objectRestriction][moneyRestriction]);

    return 0;
}
