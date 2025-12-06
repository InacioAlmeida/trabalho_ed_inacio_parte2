#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partida.h" 

typedef struct bddepartidas BDPartidas;

BDPartidas* criar_bd_partidas();
void deletar_bd_partidas(BDPartidas* bdp);
int carregar_bd_partidas(BDPartidas* bdp, const char* filename);
Partida** get_todas_partidas_bd(BDPartidas* bdp, int* count);

int adicionar_partida_ao_bd(BDPartidas* bdp, int id_time1, int id_time2, int gols1, int gols2);

/*
 * Busca uma única partida pelo ID.
 * Retorna o ponteiro para a partida ou NULL se não encontrar.
 */
Partida* get_partida_bd_por_id(BDPartidas* bdp, int id);

/*
 * Remove uma partida do banco de dados (da lista).
 * Retorna 0 em sucesso, -1 se o ID não existir.
 */
int remover_partida_bd(BDPartidas* bdp, int id);

/*
 * Atualiza o placar de uma partida pelo ID.
 * Retorna 0 em sucesso, -1 se o ID não existir.
 */
int atualizar_placar_partida_bd(BDPartidas* bdp, int id, int gols1, int gols2);

#endif