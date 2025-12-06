/*
 * Ponto de entrada principal do programa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "time.h"
#include "partida.h"
#include "bd_times.h"
#include "bd_partidas.h"
#include "campeonato.h"

// --- Protótipos Auxiliares ---
void limpar_tela();
void pausar_tela();
char ler_opcao();
void imprimir_menu_principal();
void imprimir_cabecalho_tabela();

// Funções do menu
void executar_consulta_time(BDTimes* bdt);
// ALTERADO: Agora retorna int (1 para sair, 0 para continuar)
int executar_consulta_partidas(BDTimes* bdt, BDPartidas* bdp);
void executar_inserir_partida(BDTimes* bdt, BDPartidas* bdp);
void executar_atualizar_partida(BDTimes* bdt, BDPartidas* bdp);
void executar_remover_partida(BDTimes* bdt, BDPartidas* bdp);
void imprimir_tabela_classificacao(BDTimes* bdt);

// --- Função Principal ---

int main() {
    BDTimes* bdt = criar_bd_times();
    BDPartidas* bdp = criar_bd_partidas();

    if (bdt == NULL || bdp == NULL) {
        printf("Erro fatal: Falha ao alocar memória.\n");
        return 1;
    }

    if (carregar_bd_times(bdt, "dados/times.csv") != 0) {
        printf("Erro ao carregar times.csv.\n");
        return 1;
    }
    
    if (carregar_bd_partidas(bdp, "dados/partidas_completo.csv") != 0) {
        printf("Erro ao carregar partidas.csv.\n");
        return 1;
    }

    // Inicializa estatísticas
    campeonato_calcular_estatisticas(bdt, bdp);

    char opcao;
    do {
        limpar_tela();
        imprimir_menu_principal();
        opcao = ler_opcao();
        limpar_tela();

        switch (opcao) {
            case '1':
                executar_consulta_time(bdt);
                pausar_tela();
                break;
            case '2':
                executar_consulta_partidas(bdt, bdp);
                pausar_tela();
                break;
            case '3':
                executar_atualizar_partida(bdt, bdp);
                campeonato_calcular_estatisticas(bdt, bdp);
                pausar_tela();
                break;
            case '4':
                executar_remover_partida(bdt, bdp);
                campeonato_calcular_estatisticas(bdt, bdp);
                pausar_tela();
                break;
            case '5':
                executar_inserir_partida(bdt, bdp);
                campeonato_calcular_estatisticas(bdt, bdp);
                pausar_tela();
                break;
            case '6':
                imprimir_tabela_classificacao(bdt);
                pausar_tela();
                break;
            case 'Q':
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                pausar_tela();
                break;
        }

    } while (opcao != 'Q');

    deletar_bd_times(bdt);
    deletar_bd_partidas(bdp);

    return 0;
}

// Opção 1
void executar_consulta_time(BDTimes* bdt) {
    char prefixo[100];
    limpar_tela();
    printf("--- Consultar Time ---\n");
    printf("Digite o nome ou prefixo do time: ");
    if (fgets(prefixo, sizeof(prefixo), stdin) == NULL) return;
    prefixo[strcspn(prefixo, "\n")] = 0;

    int num_encontrados = 0;
    Time** encontrados = get_times_bd_por_prefixo(bdt, prefixo, &num_encontrados);
    if (num_encontrados == 0) {
        printf("Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
        if(encontrados) free(encontrados);
        return;
    }
    imprimir_cabecalho_tabela();
    for (int i = 0; i < num_encontrados; i++) {
        Time* t = encontrados[i];
        printf("%-3d %-10s %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n",
               time_get_id(t), time_get_nome(t), time_get_vitorias(t), time_get_empates(t), time_get_derrotas(t),
               time_get_GM(t), time_get_GS(t), time_get_saldoGols(t), time_get_pontuacao(t));
    }
    free(encontrados);
}

// Opção 2 - ALTERADO: Retorna int
int executar_consulta_partidas(BDTimes* bdt, BDPartidas* bdp) {
    limpar_tela();
    printf("--- Consultar Partidas ---\n");
    printf("1 - Por time mandante\n2 - Por time visitante\n3 - Por time mandante ou visitante\n4 - Retornar\nEscolha: ");
    
    char sub_opcao = ler_opcao();
    
    // CORREÇÃO: Retorna 1 se o usuário quiser sair
    if (sub_opcao == '4') return 1; 
    
    if (sub_opcao < '1' || sub_opcao > '3') return 0;

    char prefixo[100];
    printf("Digite o nome ou prefixo do time: ");
    if (fgets(prefixo, sizeof(prefixo), stdin) == NULL) return 0;
    prefixo[strcspn(prefixo, "\n")] = 0;

    int num_times_filtro = 0;
    Time** times_filtro = get_times_bd_por_prefixo(bdt, prefixo, &num_times_filtro);
    if (num_times_filtro == 0) { printf("Nenhum time encontrado.\n"); if(times_filtro) free(times_filtro); return 0; }

    int num_partidas_total = 0;
    Partida** todas_partidas = get_todas_partidas_bd(bdp, &num_partidas_total);
    printf("\nPartidas encontradas:\nID  Time1        x   Time2\n----------------------------------\n");

    int count = 0;
    for (int i = 0; i < num_partidas_total; i++) {
        Partida* p = todas_partidas[i];
        int id1 = partida_get_id_time1(p);
        int id2 = partida_get_id_time2(p);
        bool match = false;
        for (int j = 0; j < num_times_filtro; j++) {
            int idf = time_get_id(times_filtro[j]);
            if ((sub_opcao=='1' && id1==idf) || (sub_opcao=='2' && id2==idf) || (sub_opcao=='3' && (id1==idf || id2==idf))) match = true;
        }
        if (match) {
            Time *t1 = get_time_bd_por_id(bdt, id1), *t2 = get_time_bd_por_id(bdt, id2);
            printf("%-3d %-10s %d x %d %-10s\n", partida_get_id(p), t1?time_get_nome(t1):"?", partida_get_gols_time1(p), partida_get_gols_time2(p), t2?time_get_nome(t2):"?");
            count++;
        }
    }
    if(count==0) printf("Nenhuma partida encontrada.\n");
    free(times_filtro);
    
    return 0; // Retorno normal
}

// Opção 5
void executar_inserir_partida(BDTimes* bdt, BDPartidas* bdp) {
    limpar_tela();
    printf("--- Inserir Nova Partida ---\n");
    int id1, id2, gols1, gols2;
    printf("Time 1 ID: "); if(scanf("%d",&id1)!=1){fflush(stdin);return;}
    printf("Time 2 ID: "); if(scanf("%d",&id2)!=1){fflush(stdin);return;}
    printf("Placar time 1: "); if(scanf("%d",&gols1)!=1){fflush(stdin);return;}
    printf("Placar time 2: "); if(scanf("%d",&gols2)!=1){fflush(stdin);getchar();return;}
    getchar();

    Time *t1 = get_time_bd_por_id(bdt, id1), *t2 = get_time_bd_por_id(bdt, id2);
    if (!t1 || !t2 || id1 == id2) { printf("Dados inválidos.\n"); return; }

    printf("\nConfirma inserção? (S/N)\nNEW %-10s x %-10s (%d-%d)\n", time_get_nome(t1), time_get_nome(t2), gols1, gols2);
    if (ler_opcao() == 'S') {
        int id = adicionar_partida_ao_bd(bdp, id1, id2, gols1, gols2);
        printf(id != -1 ? "Sucesso. ID: %d\n" : "Erro.\n", id);
    }
}

// Opção 3
void executar_atualizar_partida(BDTimes* bdt, BDPartidas* bdp) {
    limpar_tela();
    
    // CORREÇÃO: Verifica se o usuário pediu para voltar (retornou 1)
    if (executar_consulta_partidas(bdt, bdp) == 1) {
        return; // Retorna ao menu principal imediatamente
    }
    
    printf("\nDigite o ID do registro a ser atualizado: ");
    int id;
    if (scanf("%d", &id) != 1) { fflush(stdin); return; }
    getchar(); 

    Partida* p = get_partida_bd_por_id(bdp, id);
    if (p == NULL) {
        printf("Partida com ID %d não encontrada.\n", id);
        return;
    }

    Time* t1 = get_time_bd_por_id(bdt, partida_get_id_time1(p));
    Time* t2 = get_time_bd_por_id(bdt, partida_get_id_time2(p));

    printf("\nDados Atuais:\n");
    printf("ID: %d | %s %d x %d %s\n", 
           id, time_get_nome(t1), partida_get_gols_time1(p), partida_get_gols_time2(p), time_get_nome(t2));

    char buf[20];
    int novo_gols1 = partida_get_gols_time1(p);
    int novo_gols2 = partida_get_gols_time2(p);

    printf("Digite o novo placar para %s (ou '-' para manter): ", time_get_nome(t1));
    if (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = 0;
        if (strcmp(buf, "-") != 0 && strlen(buf) > 0) {
            novo_gols1 = atoi(buf);
        }
    }

    printf("Digite o novo placar para %s (ou '-' para manter): ", time_get_nome(t2));
    if (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = 0;
        if (strcmp(buf, "-") != 0 && strlen(buf) > 0) {
            novo_gols2 = atoi(buf);
        }
    }

    printf("\nConfirma os novos valores? (S/N)\n");
    printf("%s %d x %d %s\n", time_get_nome(t1), novo_gols1, novo_gols2, time_get_nome(t2));

    if (ler_opcao() == 'S') {
        atualizar_placar_partida_bd(bdp, id, novo_gols1, novo_gols2);
        printf("Registro atualizado com sucesso.\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

// Opção 4
void executar_remover_partida(BDTimes* bdt, BDPartidas* bdp) {
    limpar_tela();
    
    // CORREÇÃO: Verifica se o usuário pediu para voltar
    if (executar_consulta_partidas(bdt, bdp) == 1) {
        return;
    }

    printf("\nDigite o ID do registro a ser removido: ");
    int id;
    if (scanf("%d", &id) != 1) { fflush(stdin); return; }
    getchar();

    Partida* p = get_partida_bd_por_id(bdp, id);
    if (p == NULL) {
        printf("Partida com ID %d não encontrada.\n", id);
        return;
    }

    Time* t1 = get_time_bd_por_id(bdt, partida_get_id_time1(p));
    Time* t2 = get_time_bd_por_id(bdt, partida_get_id_time2(p));

    printf("\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n");
    printf("ID: %d | %s %d x %d %s\n", 
           id, time_get_nome(t1), partida_get_gols_time1(p), partida_get_gols_time2(p), time_get_nome(t2));

    if (ler_opcao() == 'S') {
        if (remover_partida_bd(bdp, id) == 0) {
            printf("Registro removido com sucesso.\n");
        } else {
            printf("Erro ao remover registro.\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}

void imprimir_tabela_classificacao(BDTimes* bdt) {
    limpar_tela();
    int num_times = 0;
    Time** todos_times = get_todos_times_bd(bdt, &num_times);
    if (num_times == 0) { printf("Nenhum time cadastrado.\n"); return; }
    printf("--- Tabela de Classificação ---\n");
    imprimir_cabecalho_tabela();
    for (int i = 0; i < num_times; i++) {
        Time* t = todos_times[i];
        printf("%-3d %-10s %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n",
               time_get_id(t), time_get_nome(t), time_get_vitorias(t), time_get_empates(t), time_get_derrotas(t),
               time_get_GM(t), time_get_GS(t), time_get_saldoGols(t), time_get_pontuacao(t));
    }
}

void imprimir_menu_principal() {
    printf("==========================================\n Sistema de Gerenciamento de Partidas\n==========================================\n");
    printf("1 - Consultar time\n2 - Consultar partidas\n3 - Atualizar partida\n4 - Remover partida\n5 - Inserir partida\n6 - Imprimir tabela\nQ - Sair\n==========================================\nEscolha uma opção: ");
}

void imprimir_cabecalho_tabela() {
    printf("------------------------------------------------------------------\n%-3s %-10s %-3s %-3s %-3s %-3s %-3s %-3s %-3s\n------------------------------------------------------------------\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
}

char ler_opcao() {
    char buffer[10];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) return toupper(buffer[0]);
    return '\0';
}

void limpar_tela() { system("clear"); }
void pausar_tela() { printf("\nPressione Enter para continuar..."); getchar(); }