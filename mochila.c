#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

typedef struct tesouro{
    int moedas;
    Tesouro *prox;
}Tesouro;

Mochila* cria_mochila(){
    Mochila* li = (Mochila*)malloc(sizeof(Mochila));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_mochila(Mochila* li){
    if(li != NULL){
        Tesouro* no;
        while((*li) != NULL){
            no = li;
            *li = (*li) -> prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_mochila(Mochila* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Tesouro* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int mochila_vazia(Mochila* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

int insere_mochila_ordenado(Mochila *li, int moedas){
    if(li == NULL)
        return 0;
    Tesouro *no = (Tesouro*)malloc(sizeof(Tesouro));
    if(no == NULL)
        return 0;
    no->moedas = moedas;
    if(mochila_vazia(li)){
        no->prox = (*li);
        li = no;
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