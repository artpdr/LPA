#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <limits.h>
#include <map>

#define N 10000

struct Turno{
    int entrada;
    int saida;
};

Turno turnos[N];
int num_enferm;
int tempo_maximo;
int min_enferm;

bool cstmSort (Turno i, Turno j) {
    if(i.entrada == j.entrada){
        return (i.saida > j.saida);
    }
    return (i.entrada < j.entrada);
}

bool findMin(int num_turno, int tempo_fim, int num_enferm_actual){
    if (tempo_fim == tempo_maximo){
        min_enferm = num_enferm_actual;
        return true;
    }

    std::map<int, int> turnos_sobrepostos;
    int i;
    for(i = num_turno+1; i<num_enferm && turnos[i].entrada < turnos[num_turno].saida; i++){
        turnos_sobrepostos[turnos[i].saida] = i;
    }

    if(i < num_enferm && turnos[i].entrada == turnos[num_turno].saida){
        return findMin(i, turnos[i].saida, num_enferm_actual);
    }
    else{
        for(std::map<int, int>::reverse_iterator it = turnos_sobrepostos.rbegin(); it != turnos_sobrepostos.rend(); it++){
            if(findMin(it->second, it->first, num_enferm_actual+1)){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d", &num_enferm);

    tempo_maximo = 0;

    for (int i = 0; i < num_enferm; i++){
        scanf("%d %d", &turnos[i].entrada, &turnos[i].saida);
        if(turnos[i].saida > tempo_maximo){
            tempo_maximo = turnos[i].saida;
        }
    }

    std::sort(turnos, turnos+num_enferm, cstmSort);

    min_enferm = INT_MAX;

    findMin(0, turnos[0].saida, 1);

    printf("%d\n", min_enferm);

    return 0;
}
