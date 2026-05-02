#ifndef MOCHILA_H
#define MOCHILA_H

/*
    Tipo abstrato da mochila.
    Internamente, ela é uma lista encadeada de tesouros, implementada em mochila.c.
*/
typedef struct tesouro* Mochila;

/* Funções da lista/mochila */
Mochila* cria_mochila(void);
void libera_mochila(Mochila* mochila);
int mochila_vazia(Mochila* mochila);
int tamanho_mochila(Mochila* mochila);
int soma_mochila(Mochila* mochila);
int insere_mochila_ordenado(Mochila* mochila, int moedas);
int remove_inicio_mochila(Mochila* mochila);
int exibe_elementos_mochila(Mochila* mochila);

#endif
