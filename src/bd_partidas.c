#include "bd_partidas.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_partida {
    Partida* partida;
    struct node_partida* next;
} NodePartida;

struct bddepartidas {
    NodePartida* head;
    int count;
    Partida** vetor_cache; 
};

BDPartidas* criar_bd_partidas() {
    BDPartidas* bdp = malloc(sizeof(struct bddepartidas));
    if (bdp != NULL) {
        bdp->head = NULL;
        bdp->count = 0;
        bdp->vetor_cache = NULL;
    }
    return bdp;
}

void deletar_bd_partidas(BDPartidas* bdp) {
    if (bdp == NULL) return;
    
    NodePartida* atual = bdp->head;
    while (atual != NULL) {
        NodePartida* temp = atual;
        atual = atual->next;
        deletar_partida(temp->partida);
        free(temp);
    }
    
    if (bdp->vetor_cache != NULL) free(bdp->vetor_cache);
    free(bdp);
}

void adicionar_partida_na_lista(BDPartidas* bdp, Partida* p) {
    NodePartida* novo = malloc(sizeof(NodePartida));
    novo->partida = p;
    novo->next = NULL;

    if (bdp->head == NULL) {
        bdp->head = novo;
    } else {
        NodePartida* atual = bdp->head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }
    bdp->count++;

    if (bdp->vetor_cache != NULL) {
        free(bdp->vetor_cache);
        bdp->vetor_cache = NULL;
    }
}

int gerar_proximo_id(BDPartidas* bdp) {
    int max_id = -1;
    NodePartida* atual = bdp->head;
    while (atual != NULL) {
        int pid = partida_get_id(atual->partida);
        if (pid > max_id) max_id = pid;
        atual = atual->next;
    }
    return max_id + 1;
}

int carregar_bd_partidas(BDPartidas* bdp, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return -1;
    }
    char buffer[256];
    fgets(buffer, sizeof(buffer), f); 
    int id, id1, id2, gols1, gols2;
    while (fscanf(f, "%d,%d,%d,%d,%d", &id, &id1, &id2, &gols1, &gols2) == 5) {
        Partida* p = criar_partida(id, id1, id2, gols1, gols2); 
        adicionar_partida_na_lista(bdp, p);
    }
    fclose(f);
    return 0;
}

Partida** get_todas_partidas_bd(BDPartidas* bdp, int* count) {
    *count = bdp->count;
    if (bdp->vetor_cache != NULL) return bdp->vetor_cache;
    if (bdp->count == 0) return NULL;

    bdp->vetor_cache = malloc(sizeof(Partida*) * bdp->count);
    NodePartida* atual = bdp->head;
    int i = 0;
    while (atual != NULL) {
        bdp->vetor_cache[i] = atual->partida;
        atual = atual->next;
        i++;
    }
    return bdp->vetor_cache;
}

int adicionar_partida_ao_bd(BDPartidas* bdp, int id_time1, int id_time2, int gols1, int gols2) {
    int novo_id = gerar_proximo_id(bdp);
    Partida* p = criar_partida(novo_id, id_time1, id_time2, gols1, gols2);
    if (p == NULL) return -1; 
    adicionar_partida_na_lista(bdp, p);
    return novo_id;
}

Partida* get_partida_bd_por_id(BDPartidas* bdp, int id) {
    NodePartida* atual = bdp->head;
    while (atual != NULL) {
        if (partida_get_id(atual->partida) == id) {
            return atual->partida;
        }
        atual = atual->next;
    }
    return NULL;
}

int remover_partida_bd(BDPartidas* bdp, int id) {
    NodePartida* atual = bdp->head;
    NodePartida* anterior = NULL;

    while (atual != NULL) {
        if (partida_get_id(atual->partida) == id) {
            // Encontrou. Ajustar ponteiros.
            if (anterior == NULL) {
                bdp->head = atual->next;
            } else {
                anterior->next = atual->next;
            }

            // Liberar memória
            deletar_partida(atual->partida);
            free(atual);
            bdp->count--;

            // Invalidar cache
            if (bdp->vetor_cache != NULL) {
                free(bdp->vetor_cache);
                bdp->vetor_cache = NULL;
            }
            return 0; // Sucesso
        }
        anterior = atual;
        atual = atual->next;
    }
    return -1; // Não encontrado
}

int atualizar_placar_partida_bd(BDPartidas* bdp, int id, int gols1, int gols2) {
    Partida* p = get_partida_bd_por_id(bdp, id);
    if (p != NULL) {
        partida_set_placar(p, gols1, gols2);
        return 0; // Sucesso
    }
    return -1; // Não encontrado
}
