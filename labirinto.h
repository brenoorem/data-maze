#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include "mochila.h"

/*
    Tamanho máximo do labirinto.
    Como o enunciado permite até 40x40, o vetor precisa comportar 1600 posições.
*/
#define MAX_LAB 1600

/*
    Estrutura que representa uma posição do personagem no labirinto.
    posX representa a coluna e posY representa a linha.
*/
typedef struct personagem{
    int posX;
    int posY;
} Personagem;

/*
    Tipo abstrato da pilha do caminho.
    A struct posicao é implementada no arquivo labirinto.c.
*/
typedef struct posicao* Labirinto;

/* Funções da pilha usada para guardar o caminho percorrido */
Labirinto* cria_labirinto(void);
void libera_labirinto(Labirinto* pilha);
int insere_posicao(Labirinto* pilha, Personagem p);
int remove_posicao(Labirinto* pilha);
Personagem ultima_posicao(Labirinto* pilha);
int qtd_posicoes(Labirinto* pilha);
int pilha_vazia(Labirinto* pilha);
void grava_caminho_arquivo(Labirinto* pilha, FILE* arquivo);

/* Funções relacionadas ao mapa, movimentação e busca da saída */
int carrega_labirinto(char labirinto[MAX_LAB], int* linhas, int* colunas, const char* nome_arquivo);
Personagem encontra_personagem(char labirinto[MAX_LAB], int linhas, int colunas, char simbolo);
int pos_2d_para_linear(int x, int y, int colunas);
int pode_mover(char labirinto[MAX_LAB], int x, int y, int colunas, int linhas, char visitados[MAX_LAB]);
int backtracking(Personagem atual, Personagem saida, char labirinto[MAX_LAB], char visitados[MAX_LAB], Labirinto* caminho, int colunas, int linhas, Mochila* mochila);
void imprime_labirinto(char labirinto[MAX_LAB], int linhas, int colunas, Personagem atual);

#endif
