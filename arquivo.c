#include <stdio.h>
#include "arquivo.h"

/*
    Função responsável por gravar o resultado final do jogo em um arquivo .txt.
    Ela recebe o caminho encontrado, o valor total dos tesouros e o nome do
    arquivo onde a solução será salva.
*/
int salva_solucao(Labirinto* caminho, int valor_total, const char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL){
        printf("ERRO: nao foi possivel criar o arquivo %s\n", nome_arquivo);
        return 0;
    }

    /*
        Grava as informações principais da solução:
        - caminho correto da entrada até a saída;
        - quantidade de passos;
        - valor total dos tesouros restantes na mochila.
    */
    fprintf(arquivo, "=== SOLUCAO DO LABIRINTO ===\n\n");
    fprintf(arquivo, "Caminho correto da entrada ate a saida:\n");
    grava_caminho_arquivo(caminho, arquivo);
    fprintf(arquivo, "\nTotal de passos: %d\n", qtd_posicoes(caminho));
    fprintf(arquivo, "Valor total dos tesouros: %d moedas\n", valor_total);
    fprintf(arquivo, "\nSaida encontrada com sucesso!\n");

    fclose(arquivo);
    return 1;
}
