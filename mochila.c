#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

/*
    Cada nó da lista representa um tesouro armazenado na mochila.
    O campo moedas guarda o valor do tesouro.
*/
struct tesouro{
    int moedas;
    struct tesouro *prox;
};

/* Cria a mochila como uma lista encadeada inicialmente vazia. */
Mochila* cria_mochila(void){
    Mochila* mochila = malloc(sizeof(Mochila));
    if(mochila != NULL){
        *mochila = NULL;
    }
    return mochila;
}

/* Libera todos os nós da lista e depois libera o ponteiro principal da mochila. */
void libera_mochila(Mochila* mochila){
    if(mochila == NULL) return;

    Mochila atual = *mochila;
    while(atual != NULL){
        Mochila remover = atual;
        atual = atual->prox;
        free(remover);
    }

    free(mochila);
}

int mochila_vazia(Mochila* mochila){
    return mochila == NULL || *mochila == NULL;
}

/* Conta quantos tesouros existem na mochila. */
int tamanho_mochila(Mochila* mochila){
    if(mochila == NULL) return 0;

    int qtd = 0;
    Mochila atual = *mochila;
    while(atual != NULL){
        qtd++;
        atual = atual->prox;
    }
    return qtd;
}

/* Soma o valor de todos os tesouros presentes na mochila. */
int soma_mochila(Mochila* mochila){
    if(mochila == NULL) return 0;

    int total = 0;
    Mochila atual = *mochila;
    while(atual != NULL){
        total += atual->moedas;
        atual = atual->prox;
    }
    return total;
}

/*
    Insere um novo tesouro mantendo a mochila em ordem crescente.
    Assim, o menor tesouro fica sempre na primeira posição e será removido
    primeiro caso o personagem caia em uma armadilha.
*/
int insere_mochila_ordenado(Mochila* mochila, int moedas){
    if(mochila == NULL) return 0;

    Mochila novo = malloc(sizeof(struct tesouro));
    if(novo == NULL) return 0;

    novo->moedas = moedas;
    novo->prox = NULL;

    if(*mochila == NULL || moedas <= (*mochila)->moedas){
        novo->prox = *mochila;
        *mochila = novo;
        return 1;
    }

    Mochila atual = *mochila;
    while(atual->prox != NULL && atual->prox->moedas < moedas){
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    return 1;
}

/*
    Remove o primeiro item da mochila.
    Pela regra da atividade, a armadilha remove o tesouro que está na primeira posição.
*/
int remove_inicio_mochila(Mochila* mochila){
    if(mochila_vazia(mochila)) return 0;

    Mochila remover = *mochila;
    *mochila = remover->prox;
    free(remover);
    return 1;
}

/* Exibe os tesouros atuais da mochila e o valor total acumulado. */
int exibe_elementos_mochila(Mochila* mochila){
    if(mochila_vazia(mochila)){
        printf("Mochila vazia\n");
        return 0;
    }

    printf("Mochila: ");
    Mochila atual = *mochila;
    while(atual != NULL){
        printf("%d ", atual->moedas);
        atual = atual->prox;
    }
    printf("| Total: %d moedas\n", soma_mochila(mochila));
    return 1;
}
