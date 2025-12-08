#include "campeonato.h"
#include <stdlib.h> 

void campeonato_calcular_estatisticas(BDTimes* bdt, BDPartidas* bdp) {
    //Zera estatísticas anteriores de TODOS os times
    int num_times = 0;
    Time** todos_times = get_todos_times_bd(bdt, &num_times);
    
    // Se não houver times, não há o que calcular
    if (num_times == 0) return;

    for (int i = 0; i < num_times; i++) {
        time_zerar_estatisticas(todos_times[i]);
    }

    //Processa todas as partidas atuais da lista
    int num_partidas = 0;
    Partida** todas_partidas = get_todas_partidas_bd(bdp, &num_partidas);
    
    if (num_partidas == 0) return;

    for (int i = 0; i < num_partidas; i++) {
        Partida* p = todas_partidas[i];

        int id_time1 = partida_get_id_time1(p);
        int id_time2 = partida_get_id_time2(p);
        int gols_time1 = partida_get_gols_time1(p);
        int gols_time2 = partida_get_gols_time2(p);

        Time* time1 = get_time_bd_por_id(bdt, id_time1);
        Time* time2 = get_time_bd_por_id(bdt, id_time2);

        if (time1 != NULL && time2 != NULL) {
            atualizar_estatisticas_time(time1, gols_time1, gols_time2);
            atualizar_estatisticas_time(time2, gols_time2, gols_time1);
        }
    }
}
