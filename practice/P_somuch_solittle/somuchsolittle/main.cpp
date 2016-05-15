#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#define N 200

struct Activity{
    int start;
    int end_;
};

Activity activities[N];
int num_activities;

bool comparator(Activity i, Activity j){
    return (i.end_ < j.end_);
}

int max_activities(){
    int max_num_activities = 1;
    int running_act_end = activities[0].end_;
    for(int i = 1; i < num_activities; i++){
        if(activities[i].start < running_act_end){
            continue;
        }
        running_act_end = activities[i].end_;
        max_num_activities++;
    }
    return max_num_activities;
}

int main()
{
    scanf("%d", &num_activities);
    for(int i = 0; i < num_activities; i++){
        scanf("%d %d", &activities[i].start, &activities[i].end_);
    }

    if(num_activities>0){
        std::sort(activities, activities+num_activities, comparator);

        printf("%d\n", max_activities());
    }
    else{
        printf("0\n");
    }
    return 0;
}
