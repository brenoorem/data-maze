#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

// estrutura tesouro (conteúdo da mochila (lista))
typedef struct tesouro{
    int moedas;
    struct tesouro *prox;
}Tesouro;

// função que realiza a criação de uma mochila (lista)
Mochila* cria_mochila(){
    Mochila* li = (Mochila*)malloc(sizeof(Mochila));
    if(li != NULL)
        *li = NULL;
    return li;
}

// função que libera memória alocada para a mochila
void libera_mochila(Mochila* li){
    if(li != NULL){
        Tesouro* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li) -> prox;
            free(no);
        }
        free(li);
    }
}

// função que indica quantos elementos há na mochila
int tamanho_mochila(Mochila* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Mochila no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

// função que indica se a mochila está vazia
int mochila_vazia(Mochila* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

// função que insere os tesouros na mochila de forma ordenada
int insere_mochila_ordenado(Mochila *li, int moedas){
    if(li == NULL)
        return 0;
    Tesouro *no = (Tesouro*)malloc(sizeof(Tesouro));
    if(no == NULL)
        return 0;
    no->moedas = moedas;
    if(mochila_vazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    }
    else{
        Tesouro *ant, *atual = *li;
        while(atual != NULL && atual->moedas < moedas){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }
        else{
            no->prox = ant->prox;
            ant->prox = no;
        }
    }
    return 1;
}

// função que remove o primeiro item da mochila
int remove_inicio_mochila(Mochila *li){
    if(li==NULL)
        return 0;
    if((*li)==NULL)
        return 0;
    Tesouro* no = *li;
    *li = no->prox;
    free(no);
}

// função que imprime o conteúdo atual da mochila
int exibe_elementos_mochila(Mochila *li){
    if(li==NULL)
        return 0;
    Tesouro* no = *li;
    while(no != NULL){
        printf("%d | ", no->moedas);
        no = no->prox;
    }
    printf("\n");
    return 1;
}