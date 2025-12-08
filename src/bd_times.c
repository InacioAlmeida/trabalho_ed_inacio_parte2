#include "bd_times.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da lista encadeada de times
typedef struct node_time {
    Time* time;
    struct node_time* next;
} NodeTime;

struct bddetimes {
    NodeTime* head;      
    int count;           
    Time** vetor_cache;  
};

BDTimes* criar_bd_times() {
    BDTimes* bdt = malloc(sizeof(struct bddetimes));
    if (bdt != NULL) {
        bdt->head = NULL;
        bdt->count = 0;
        bdt->vetor_cache = NULL;
    }
    return bdt;
}

void deletar_bd_times(BDTimes* bdt) {
    if (bdt == NULL) return;

    NodeTime* atual = bdt->head;
    while (atual != NULL) {
        NodeTime* temp = atual;
        atual = atual->next;
        deletar_time(temp->time); 
        free(temp);               
    }

    if (bdt->vetor_cache != NULL) {
        free(bdt->vetor_cache);
    }

    free(bdt);
}

void adicionar_time_na_lista(BDTimes* bdt, Time* t) {
    NodeTime* novo = malloc(sizeof(NodeTime));
    novo->time = t;
    novo->next = NULL;

    if (bdt->head == NULL) {
        bdt->head = novo;
    } else {
        NodeTime* atual = bdt->head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }
    bdt->count++;

    if (bdt->vetor_cache != NULL) {
        free(bdt->vetor_cache);
        bdt->vetor_cache = NULL;
    }
}

int carregar_bd_times(BDTimes* bdt, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return -1; 
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), f); 

    int id;
    char nome[100];
    
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (sscanf(buffer, "%d,%99[^\n]", &id, nome) == 2) {
            Time* t = criar_time(id, nome); 
            adicionar_time_na_lista(bdt, t);
        }
    }

    fclose(f);
    return 0;
}

Time* get_time_bd_por_id(BDTimes* bdt, int id) {
    NodeTime* atual = bdt->head;
    while (atual != NULL) {
        if (time_get_id(atual->time) == id) {
            return atual->time;
        }
        atual = atual->next;
    }
    return NULL;
}

// Função comparadora para o qsort
// Retorna <0 se a vem antes de b (decrescente), >0 se b vem antes, 0 se iguais
int comparar_times(const void* a, const void* b) {
    Time* timeA = *(Time**)a;
    Time* timeB = *(Time**)b;

    // 1. Pontos (Decrescente)
    int pgA = time_get_pontuacao(timeA);
    int pgB = time_get_pontuacao(timeB);
    if (pgA != pgB) return pgB - pgA;

    // 2. Vitórias (Decrescente)
    int vA = time_get_vitorias(timeA);
    int vB = time_get_vitorias(timeB);
    if (vA != vB) return vB - vA;

    // 3. Saldo de Gols (Decrescente)
    int sA = time_get_saldoGols(timeA);
    int sB = time_get_saldoGols(timeB);
    if (sA != sB) return sB - sA;

    return time_get_id(timeA) - time_get_id(timeB);
}

Time** get_todos_times_bd(BDTimes* bdt, int* count) {
    *count = bdt->count;
    
    if (bdt->vetor_cache != NULL) {
        return bdt->vetor_cache;
    }

    if (bdt->count == 0) return NULL;

    // Gera o cache
    bdt->vetor_cache = malloc(sizeof(Time*) * bdt->count);
    NodeTime* atual = bdt->head;
    int i = 0;
    while (atual != NULL) {
        bdt->vetor_cache[i] = atual->time;
        atual = atual->next;
        i++;
    }

    // Ordena o cache antes de entregar
    qsort(bdt->vetor_cache, bdt->count, sizeof(Time*), comparar_times);
    
    return bdt->vetor_cache;
}

Time** get_times_bd_por_prefixo(BDTimes* bdt, const char* prefixo, int* count) {
    *count = 0;
    Time** resultados = malloc(sizeof(Time*) * bdt->count); 
    if (resultados == NULL) return NULL;

    int tam_prefixo = strlen(prefixo);
    NodeTime* atual = bdt->head;

    while (atual != NULL) {
        const char* nome_time = time_get_nome(atual->time);
        if (strncmp(nome_time, prefixo, tam_prefixo) == 0) {
            resultados[*count] = atual->time;
            (*count)++;
        }
        atual = atual->next;
    }

    return resultados;
}
