#include <stdio.h>
#include "mochila.h"

int main(){
    Mochila *mochila = cria_mochila();

    insere_mochila_ordenado(mochila, 5);
    insere_mochila_ordenado(mochila, 3);
    insere_mochila_ordenado(mochila, 2);

    printf("%i", tamanho_mochila(mochila));

    return 0;
}