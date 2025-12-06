# 🏆 Trabalho Prático - Campeonato Computacional de Futebol (Parte II)

Este projeto é um sistema de linha de comando (CLI) desenvolvido em C para gerenciamento completo (CRUD) e consulta de dados de um campeonato de futebol.

Esta é a **Parte II** do trabalho, que expande o sistema original adicionando suporte a manutenção de dados (Inserir, Atualizar, Remover) e implementando estruturas de dados dinâmicas (**Listas Encadeadas**) e ordenação por mérito esportivo.

## 🚀 Novas Funcionalidades (Parte II)

Além das consultas da Parte I, o sistema agora suporta:

* **Listas Encadeadas:** Substituição dos vetores estáticos por alocação dinâmica nó a nó, permitindo um número indefinido de registros (limitado apenas pela memória).
* **Inserir Partida (Opção 5):** Permite cadastrar novos jogos com geração automática de ID (Auto-Incremento).
* **Atualizar Partida (Opção 3):** Permite alterar o placar de jogos existentes.
* **Remover Partida (Opção 4):** Permite excluir jogos do banco de dados.
* **Recálculo Dinâmico:** As estatísticas (Pontos, Vitórias, etc.) são recalculadas automaticamente e corretamente sempre que uma partida é alterada.
* **Ordenação (Opção 6):** A tabela de classificação é exibida ordenada decrescentemente pelos critérios: **Pontos > Vitórias > Saldo de Gols**.

## 📂 Estrutura de Arquivos