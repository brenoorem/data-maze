#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "labirinto.h"
#include "arquivo.h"

int main(void){
    /*
        Inicializa a geração de números aleatórios.
        Isso é necessário porque o valor dos tesouros é sorteado durante o jogo.
    */
    srand(time(NULL));

    char labirinto[MAX_LAB];
    char visitados[MAX_LAB];
    int linhas = 0;
    int colunas = 0;

    /*
        Inicializa os vetores com espaços em branco.
        O vetor labirinto guarda o mapa e o vetor visitados controla
        as posições que já foram percorridas pelo algoritmo.
    */
    for(int i = 0; i < MAX_LAB; i++){
        labirinto[i] = ' ';
        visitados[i] = ' ';
    }

    /*
        Carrega o labirinto a partir do arquivo texto.
        Caso o arquivo não exista ou esteja inválido, o programa é encerrado.
    */
    if(!carrega_labirinto(labirinto, &linhas, &colunas, "labirinto.txt")){
        return 1;
    }

    /*
        Localiza a posição inicial do personagem (P) e a saída (S).
    */
    Personagem inicio = encontra_personagem(labirinto, linhas, colunas, 'P');
    Personagem saida = encontra_personagem(labirinto, linhas, colunas, 'S');

    if(inicio.posX == 0 || saida.posX == 0){
        printf("ERRO: o labirinto precisa ter P e S.\n");
        return 1;
    }

    /*
        Cria as estruturas principais:
        - caminho: pilha usada para guardar o percurso correto;
        - mochila: lista encadeada ordenada com os tesouros coletados.
    */
    Labirinto* caminho = cria_labirinto();
    Mochila* mochila = cria_mochila();

    if(caminho == NULL || mochila == NULL){
        printf("ERRO: falha ao alocar memoria.\n");
        libera_labirinto(caminho);
        libera_mochila(mochila);
        return 1;
    }

    printf("Dimensoes: %d colunas x %d linhas\n", colunas, linhas);
    printf("Inicio: X=%d, Y=%d\n", inicio.posX, inicio.posY);
    printf("Saida: X=%d, Y=%d\n", saida.posX, saida.posY);
    printf("\nRodando em 5s...\n");

    Sleep(5000);

    /*
        Executa o algoritmo de backtracking.
        Se a saída for encontrada, mostra os resultados e salva a solução.
    */
    if(backtracking(inicio, saida, labirinto, visitados, caminho, colunas, linhas, mochila)){
        int total = soma_mochila(mochila);

        printf("\nSAIDA ENCONTRADA COM SUCESSO!\n");
        printf("Total de passos: %d\n", qtd_posicoes(caminho));
        printf("Valor total dos tesouros: %d moedas\n", total);

        salva_solucao(caminho, total, "saida.txt");
        printf("Solucao salva em saida.txt\n");
    }
    else{
        printf("\nSAIDA NAO ENCONTRADA!\n");
    }

    /*
        Libera a memória alocada para evitar vazamento de memória.
    */
    libera_labirinto(caminho);
    libera_mochila(mochila);

    return 0;
}
