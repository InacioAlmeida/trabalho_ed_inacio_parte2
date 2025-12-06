# 🏆 Trabalho Prático - Campeonato Computacional de Futebol (Parte II)

Este projeto é um sistema de linha de comando (CLI) desenvolvido em C para gerenciamento completo e consulta de dados de um campeonato de futebol.

Esta é a **Parte II** do trabalho acadêmico, que evolui o sistema original substituindo estruturas estáticas por **Listas Encadeadas** e implementando funcionalidades de manutenção de dados (Inserir, Atualizar, Remover) e ordenação por mérito esportivo, conforme especificado nos requisitos.

## 🚀 Novas Funcionalidades (Parte II)

Além das funcionalidades de leitura da Parte I, o sistema agora suporta:

* **Estruturas Dinâmicas:** Utilização de **Listas Simplesmente Encadeadas** para armazenar times e partidas, permitindo manipulação dinâmica de memória sem limites fixos de tamanho.
* **Inserir Partida (Opção 5):** Cadastro de novos jogos com geração automática de ID (Auto-Incremento).
* **Atualizar Partida (Opção 3):** Alteração de placares de jogos já existentes, com reflexo imediato na tabela.
* **Remover Partida (Opção 4):** Exclusão de jogos do sistema, revertendo os pontos e estatísticas dos times envolvidos.
* **Ordenação (Opção 6):** A tabela de classificação é exibida ordenada decrescentemente por mérito esportivo: **Pontos (PG) > Vitórias (V) > Saldo de Gols (S)**.
* **Recálculo Automático:** Integridade dos dados garantida através de uma estratégia de recálculo total das estatísticas após qualquer alteração.

## 📂 Estrutura de Arquivos

O projeto mantém a organização modular:

```text
trabalho_2/
├── Makefile               # Script de compilação
├── include/               # Interfaces (Headers) dos TADs
│   ├── bd_partidas.h      # Gerenciador de Partidas (Lista Encadeada)
│   ├── bd_times.h         # Gerenciador de Times (Lista Encadeada)
│   ├── campeonato.h       # Lógica de negócio (Cálculo de estatísticas)
│   ├── partida.h          # Modelo de dados Partida
│   └── time.h             # Modelo de dados Time
├── src/                   # Implementação (.c)
│   ├── bd_partidas.c      # Implementação da lista e operações CRUD
│   ├── bd_times.c         # Implementação da lista e ordenação (qsort)
│   ├── campeonato.c       # Lógica de "Zerar e Recalcular"
│   ├── main.c             # Interface de Usuário (Menu e Validações)
│   ├── partida.c
│   └── time.c
└── dados/                 # Base de dados CSV
    ├── partidas_completo.csv
    ├── partidas_parcial.csv
    ├── partidas_vazio.csv
    └── times.csv