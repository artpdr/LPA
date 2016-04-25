#include <cstdlib>
#include <cstdio>
#include <map>

struct Papers_Production{
    //The key is the budget and the value is the number of papers
    std::map <int, int> num_papers;
};

Papers_Production papers[200];
int dp[200][5001];
int num_proposals[200];
//int count = 0;

int max_papers(int person, int budget){
    //count++;
    if(dp[person][budget] > -1)
        return dp[person][budget];

    if(person == 0){
        int tmp_max = 0;
        std::map<int, int>::iterator it;
        for (it = papers[person].num_papers.begin(); it != papers[person].num_papers.end(); it++){
            if(it->first > budget)
                break;
            else if(it->second > tmp_max){
                tmp_max = it->second;
            }
        }
        return dp[person][budget] = tmp_max;
    }

    int tmp_max = 0;
    int max_for_person = 0;
    std::map<int, int>::iterator it;
    //with a project from this researcher
    for (it = papers[person].num_papers.begin(); it != papers[person].num_papers.end(); it++){
        if(it->first > budget)
            break;
        else{
            tmp_max = it->second + max_papers(person-1, budget - it->first);
            if(tmp_max > max_for_person)
                max_for_person = tmp_max;
        }
    }

    //without a project from this researcher
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
            /*the researcher i may already have a proposal for this amount and we just want the one that produces more papers*/
            if(papers[i].num_papers[tmp_amount] == 0)
                papers[i].num_papers[tmp_amount] = tmp_papers;
            else if(papers[i].num_papers[tmp_amount] < tmp_papers)
                papers[i].num_papers[tmp_amount] = tmp_papers;
        }
    }

    printf("%d\n", max_papers(n-1, m));

    //printf("Num calls: %d\n", count);

    return 0;
}
