#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 200
#define M 2000

struct Friend{
    int friendship;
    int num_ingredients;
    int ids_ingredients[3];
};

//int counter;
int num_ingredients;
int num_friends;
int best_min;
Friend friends[M+1];

char ingredients[N+1];

int friendship_dp[N+1]; //saves bound for unknown ingredients from 0 to n

int bound(int ingr_id){
    //counter++;
    int sum_min = 0, unwanted_ingr_found, num_unwanted_ingr_friend, wanted_ingr_found;

    for(int i = 1; i <= num_friends; i++){
        unwanted_ingr_found = 0; num_unwanted_ingr_friend = 0; wanted_ingr_found = 0;
        for(int j = 0; j < friends[i].num_ingredients; j++){
            if(friends[i].ids_ingredients[j] > 0 && (friends[i].ids_ingredients[j] < ingr_id || ingredients[friends[i].ids_ingredients[j]])){//wanted ingredient found in pizza ingredients
                wanted_ingr_found = 1;
                break;
            }
            else if(friends[i].ids_ingredients[j] < 0){
                num_unwanted_ingr_friend++;
                if(-friends[i].ids_ingredients[j] >= ingr_id && ingredients[-friends[i].ids_ingredients[j]])//unwanted ingr found in pizza
                    unwanted_ingr_found++;
                else
                    break;
            }
        }
        if(wanted_ingr_found == 0 && unwanted_ingr_found == num_unwanted_ingr_friend){
            sum_min += friends[i].friendship;
            if(sum_min >= best_min)
                return sum_min;
        }
    }

    return sum_min;
}


void findMin(int ingr_id){
    //counter++;
    if (ingr_id == 0){
        int sum_min = 0, unwanted_ingr_found, num_unwanted_ingr_friend, wanted_ingr_found;

        for(int i = 1; i <= num_friends; i++){
            unwanted_ingr_found = 0; num_unwanted_ingr_friend = 0; wanted_ingr_found = 0;
            for(int j = 0; j < friends[i].num_ingredients; j++){
                if(friends[i].ids_ingredients[j] > 0 && ingredients[friends[i].ids_ingredients[j]]){//wanted ingredient found in pizza ingredients
                    wanted_ingr_found = 1;
                    break;
                }
                else if(friends[i].ids_ingredients[j] < 0){
                    num_unwanted_ingr_friend++;
                    if(ingredients[-friends[i].ids_ingredients[j]])//unwanted ingr found in pizza
                        unwanted_ingr_found++;
                }
            }
            if(wanted_ingr_found == 0 && unwanted_ingr_found == num_unwanted_ingr_friend){
                sum_min += friends[i].friendship;
                if(sum_min > best_min)
                    return;
            }
        }

        best_min = sum_min;

        return;
    }

    findMin(ingr_id-1);
    ingredients[ingr_id] = 1;
    if(ingr_id < num_ingredients/2 && ingr_id > 1 && bound(ingr_id) >= best_min){
        ingredients[ingr_id] = 0;
        return;
    }
    findMin(ingr_id-1);
    ingredients[ingr_id] = 0;
}

int main()
{
    int pizza_id;
    scanf("%d %d", &num_ingredients, &num_friends);

    memset(ingredients, 0, sizeof(char)* (num_ingredients+1));

    best_min = INT_MAX;

    for (int i = 1; i <= num_friends; i++){
        scanf("%d", &(friends[i].friendship));
        while(scanf("%d", &pizza_id) && pizza_id != 0){
            friends[i].ids_ingredients[friends[i].num_ingredients] = pizza_id;
            friends[i].num_ingredients++;
        }
    }

    //counter = 0;

    findMin(num_ingredients);

    printf("%d\n", best_min);

    //printf("Counter: %d\n", counter);

    return 0;
}
