# 🏆 Trabalho Prático - Campeonato Computacional de Futebol (Parte I & II)

Este trabalho é um sistema de linha de comando (CLI) desenvolvido em C para gerenciamento e consulta de dados de um campeonato de futebol.

O sistema carrega os dados de times e partidas a partir de arquivos `.csv`, processa os resultados em memória (calculando vitórias, empates, derrotas, gols, etc.) e fornece ao usuário uma interface baseada em menu para manter e consultar essas estatísticas.

Este projeto tem como base os requisitos da **Parte I** (leitura e consulta) e novas funcionalidade presentes na especificação da **Parte II** (manutenção CRUD, listas encadeadas e ordenação).

## 🚀 Funcionalidades

### Funcionalidades Base (Parte I)
* **Carregamento de Dados:** Lê os arquivos `times.csv` e `partidas_completo.csv` da pasta `dados/` para a memória na inicialização.
* **Cálculo de Estatísticas:** Processa todas as partidas carregadas para calcular e acumular:
    * Vitórias (V), Empates (E), Derrotas (D)
    * Gols Marcados (GM), Gols Sofridos (GS)
    * Saldo de Gols (S) e Pontos Ganhos (PG)
* **Opção 1: Consultar Time:** Busca o desempenho de um time usando um nome ou prefixo.
* **Opção 2: Consultar Partidas:** Busca partidas específicas por time (mandante, visitante ou ambos).

### Novas Funcionalidades (Parte II)
* **Estruturas Dinâmicas:** Substituição completa dos vetores estáticos por **Listas Simplesmente Encadeadas**, permitindo manipulação ilimitada de dados (restrito apenas pela memória RAM).
* **Opção 5: Inserir Partida:** Permite cadastrar novos jogos com geração automática de ID (Auto-Incremento).
* **Opção 3: Atualizar Partida:** Permite alterar o placar de jogos existentes, recalculando automaticamente a tabela.
* **Opção 4: Remover Partida:** Permite excluir jogos do banco de dados, revertendo os pontos e estatísticas dos times envolvidos.
* **Opção 6: Tabela Ordenada:** A tabela de classificação agora é exibida ordenada decrescentemente por mérito esportivo: **Pontos (PG) > Vitórias (V) > Saldo de Gols (S)**.
* **Consistência Automática:** Implementada estratégia de "Zerar e Recalcular" para garantir que a tabela sempre reflita fielmente o estado atual das partidas após edições ou remoções.

## 📂 Estrutura de Arquivos

O projeto está organizado na seguinte estrutura de pastas para modularidade:

```text
trabalho_ed/
├── Makefile               # Controla a compilação
├── include/               # Headers dos TADs criados
│   ├── bd_partidas.h      # Interface da Lista de Partidas
│   ├── bd_times.h         # Interface da Lista de Times
│   ├── campeonato.h       # Lógica de negócio
│   ├── partida.h
│   └── time.h
├── src/                   # Implementação (.c)
│   ├── bd_partidas.c      # Implementação de Lista Encadeada + CRUD
│   ├── bd_times.c         # Implementação de Lista Encadeada + Ordenação
│   ├── campeonato.c       # Lógica de Recálculo
│   ├── main.c             # Menu e Interface de Usuário
│   ├── partida.c
│   └── time.c
└── dados/                 # Arquivos CSV de entrada
    ├── partidas_completo.csv
    ├── partidas_parcial.csv
    ├── partidas_vazio.csv
    └── times.csv
