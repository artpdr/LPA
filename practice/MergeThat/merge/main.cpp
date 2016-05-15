#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <list>

#define N 5000

int num_files;
std::list<int> files; //contains number of records of each file

void minT(){
    int total_time = 0;
    int list_size = num_files;
    int merge_time;
    std::list<int>::iterator it;
    while(1){
        merge_time = 0;
        merge_time += files.front();
        files.pop_front();
        merge_time += files.front();
        files.pop_front();
        total_time += merge_time;
        list_size-=2;
        //insert element in a sorted way
        if(list_size == 0)
            break;
        for(it = files.begin(); it != files.end(); it++){
            if(*it > merge_time)
                break;
        }
        //insert element in the position before it
        files.insert(it, merge_time);
        list_size++;
    }

    printf("%d\n", total_time);
}

int main()
{
    int num_records;
    while(scanf("%d", &num_files) != EOF){
        for(int i = 0; i < num_files; i++){
            scanf("%d", &num_records);
            files.push_front(num_records);
        }

        //sort in ascending order of number of records
        files.sort();

        if(num_files > 1)
            minT();
        else
            printf("0\n");
    }

    return 0;
}
