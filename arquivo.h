#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "labirinto.h"

/*
    Cabeçalho das funções de arquivo.
    Aqui fica a declaração da função que salva a solução final em saida.txt.
*/
int salva_solucao(Labirinto* caminho, int valor_total, const char* nome_arquivo);

#endif
