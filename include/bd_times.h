#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "time.h" 

/*
 * Definição do TAD BDTimes (Gerenciador de Times).
 * Este TAD é responsável por carregar e armazenar em memória
 * a coleção de todos os times.
 * * Implementação: Lista Simplesmente Encadeada.
 */

typedef struct bddetimes BDTimes;

/* Cria uma nova instância do gerenciador de times. */
BDTimes* criar_bd_times();

/* Libera a memória do gerenciador, da lista e de todos os times. */
void deletar_bd_times(BDTimes* bdt);

/* Carrega os dados de times de um arquivo .csv para a memória. */
int carregar_bd_times(BDTimes* bdt, const char* filename);

/* --- Funções de Acesso --- */

/* Busca um time pelo seu ID percorrendo a lista. */
Time* get_time_bd_por_id(BDTimes* bdt, int id);

/* * Retorna um vetor com ponteiros para todos os times.
 * Nota: O vetor é gerenciado internamente pelo BDTimes para compatibilidade.
 */
Time** get_todos_times_bd(BDTimes* bdt, int* count); 

/*
 * Busca times por prefixo. Retorna um novo vetor (caller deve dar free).
 */
Time** get_times_bd_por_prefixo(BDTimes* bdt, const char* prefixo, int* count);

#endif