#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

// Estrutura interna e privada do TAD Partida.
struct partida
{
    int id;
    int id_time1;
    int id_time2;
    int gols_time1;
    int gols_time2;
};

Partida* criar_partida(int id, int id_time1, int id_time2, int gols_time1, int gols_time2){
    Partida *p = malloc(sizeof(struct partida));

    if (p == NULL){
        printf("Erro de alocação de memória da partida\n");
        return NULL;
    }

    p->id = id;
    p->id_time1 = id_time1;
    p->id_time2 = id_time2;
    p->gols_time1 = gols_time1;
    p->gols_time2 = gols_time2;

    return p;
}

void deletar_partida(Partida* p){
    free(p);
}

void partida_set_placar(Partida* p, int gols_time1, int gols_time2) {
    if (p != NULL) {
        p->gols_time1 = gols_time1;
        p->gols_time2 = gols_time2;
    }
}

// --- Implementação dos Getters ---

int partida_get_id(Partida* p){
    return p->id;
}

int partida_get_id_time1(Partida* p){
    return p->id_time1;
}

int partida_get_id_time2(Partida* p){
    return p->id_time2;
}

int partida_get_gols_time1(Partida* p){
    return p->gols_time1;
}

int partida_get_gols_time2(Partida* p){
    return p->gols_time2;
}