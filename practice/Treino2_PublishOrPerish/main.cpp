#include <iostream>
#include <cstdlib>
#include <cstdio>

struct Papers_Production{
    int budget;
    int num_papers;
};

Papers_Production papers[200][10];
int dp[200][5001];
int num_proposals[200];
//int count = 0;

void order_papers(int num_researchers){
    for(int i = 0; i < num_researchers; i++){
        for(int j = 1; j < num_proposals[i]; j++){
            int k = j-1;
            Papers_Production selected = papers[i][j];
            for(;k >= 0 && papers[i][k].budget > selected.budget; k--){
                papers[i][k+1] = papers[i][k];
            }
            papers[i][k+1] = selected;
        }
    }
}

int max_papers(int person, int budget){
    //count++;
    if(dp[person][budget] > -1)
        return dp[person][budget];

    if(person == 0){
        int tmp_max = 0;
        for(int i = 0; i < num_proposals[person]; i++){
            if(papers[person][i].budget <= budget){
                if(papers[person][i].num_papers > tmp_max)
                    tmp_max = papers[person][i].num_papers;
            }
            else
                break;
        }
        return dp[person][budget] = tmp_max;
        //return tmp_max;
    }

    int tmp_max = 0;
    int max_for_person = 0;

    for(int i = 0; i < num_proposals[person]; i++){
        if(papers[person][i].budget <= budget){
            tmp_max = papers[person][i].num_papers + max_papers(person-1, budget-papers[person][i].budget);
            if(tmp_max > max_for_person)
                max_for_person = tmp_max;
        }
        else
            break;
    }
    tmp_max = max_papers(person-1, budget);
    if(tmp_max > max_for_person)
        max_for_person = tmp_max;

    return dp[person][budget] = max_for_person;
    //return max_for_person;
}

int main()
{
    //freopen("test.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= m; j++)
            dp[i][j] = -1;
    }

    /*get num of proposals of each researcher*/
    for(int i = 0; i < n; i++){
        scanf("%d", &(num_proposals[i]));
    }

    /*get max number of papers for each amount to every researcher*/
    int tmp_papers, tmp_amount;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < num_proposals[i]; j++){
            /*assuming that amount doesn't exceed the maximum amount*/
            scanf("%d %d", &tmp_amount, &tmp_papers);
            /*we can already have a proposal for this amount for this researcher and we want the one that gives more papers*/
            for(int k = 0; k < 10; k++){
                if(papers[i][k].budget == 0){
                    papers[i][k].budget = tmp_amount;
                    papers[i][k].num_papers = tmp_papers;
                    break;
                }
                if(papers[i][k].budget == tmp_amount){
                    if(papers[i][k].num_papers < tmp_papers)
                        papers[i][k].num_papers = tmp_papers;
                    num_proposals[i]--;
                    break;
                }
            }
        }
    }

    //order proposals by budget ascending
    order_papers(n);

    printf("%d\n", max_papers(n-1, m));

    //printf("Num calls: %d\n", count);

    return 0;
}
