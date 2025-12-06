#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct time
{
    int id;
    char nome[100];
    int V; //vitorias
    int E; //empates
    int D; //derrotas
    int GM; //gols marcados
    int GS; //gols sofridos
};

Time* criar_time(int id, const char* nome){
    Time* t = malloc(sizeof(struct time));
    if (t == NULL){
        printf("Erro ao alocar memória dinamicamente para o ponteiro time\n");
        return NULL;
    }
    t->id = id;
    strcpy(t->nome, nome);
    
    // Usa a própria função interna para garantir o estado inicial
    time_zerar_estatisticas(t);

    return t;
}

void time_zerar_estatisticas(Time* t) {
    if (t != NULL) {
        t->V = 0;
        t->E = 0;
        t->D = 0;
        t->GM = 0;
        t->GS = 0;
    }
}

void atualizar_estatisticas_time(Time* t, int gols_marcados, int gols_sofridos){
    t->GM += gols_marcados;
    t->GS += gols_sofridos;

    if (gols_marcados > gols_sofridos){
        t->V++;
    } else if (gols_marcados < gols_sofridos){
        t->D++;
    } else{
        t->E++;
    }
}

void deletar_time(Time* t){
    free(t);
}

// --- Getters ---

const char* time_get_nome(Time* t) { return t->nome; }
int time_get_id(Time* t){ return t->id; }
int time_get_vitorias(Time* t){ return t->V; }
int time_get_derrotas(Time* t){ return t->D; }
int time_get_empates(Time* t){ return t->E; }
int time_get_pontuacao(Time* t){ return (t->V * 3) + t-> E; }
int time_get_saldoGols(Time* t){ return (t->GM - t->GS); }
int time_get_GM(Time* t) { return t->GM; }   
int time_get_GS(Time* t) { return t->GS; }