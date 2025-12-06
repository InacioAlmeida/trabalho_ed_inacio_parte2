#ifndef PARTIDA_H
#define PARTIDA_H

/*
 * Definição do TAD Partida.
 */

typedef struct partida Partida;

Partida* criar_partida(int id, int id_time1, int id_time2, int gols_time1, int gols_time2);
void deletar_partida(Partida* p);

/*
 * Altera o placar de uma partida existente.
 */
void partida_set_placar(Partida* p, int gols_time1, int gols_time2);

// --- Funções Getters ---
int partida_get_id(Partida* p);
int partida_get_id_time1(Partida* p);
int partida_get_id_time2(Partida* p);
int partida_get_gols_time1(Partida* p);
int partida_get_gols_time2(Partida* p);

#endif