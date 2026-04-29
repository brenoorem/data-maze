#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

int main(){
    Mochila *mochila = cria_mochila();

    insere_mochila_ordenado(mochila, 5);
    insere_mochila_ordenado(mochila, 3);
    insere_mochila_ordenado(mochila, 2);

    printf("%i", tamanho_mochila(mochila));
    system("pause");

    exibe_elementos_mochila(mochila);
    system("pause");

    remove_inicio_mochila(mochila);

    printf("%i", tamanho_mochila(mochila));
    system("pause");

    exibe_elementos_mochila(mochila);
    system("pause");
    return 0;
}