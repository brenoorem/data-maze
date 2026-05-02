#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "labirinto.h"

/*
    Nó da pilha que guarda uma posição do caminho.
    Cada nó possui a posição do personagem e um ponteiro para o próximo nó.
*/
struct posicao{
    Personagem player;
    struct posicao *prox;
};

/* Limpa a tela do console para melhorar a visualização do movimento. */
void limpa_tela(){
    system("cls");
}

/* Cria a pilha do labirinto, usada para armazenar o caminho percorrido. */
Labirinto* cria_labirinto(void){
    Labirinto* pilha = malloc(sizeof(Labirinto));
    if(pilha != NULL){
        *pilha = NULL;
    }
    return pilha;
}

/* Libera todas as posições armazenadas na pilha do caminho. */
void libera_labirinto(Labirinto* pilha){
    if(pilha == NULL) return;

    while(*pilha != NULL){
        remove_posicao(pilha);
    }

    free(pilha);
}

/*
    Insere uma nova posição no topo da pilha.
    Essa função representa o PUSH da pilha.
*/
int insere_posicao(Labirinto* pilha, Personagem p){
    if(pilha == NULL) return 0;

    Labirinto novo = malloc(sizeof(struct posicao));
    if(novo == NULL) return 0;

    novo->player = p;
    novo->prox = *pilha;
    *pilha = novo;
    return 1;
}

/*
    Remove a posição que está no topo da pilha.
    Essa função representa o POP e é usada quando o algoritmo precisa voltar.
*/
int remove_posicao(Labirinto* pilha){
    if(pilha == NULL || *pilha == NULL) return 0;

    Labirinto remover = *pilha;
    *pilha = remover->prox;
    free(remover);
    return 1;
}

/* Retorna a última posição inserida na pilha. */
Personagem ultima_posicao(Labirinto* pilha){
    Personagem vazio = {0, 0};
    if(pilha == NULL || *pilha == NULL) return vazio;
    return (*pilha)->player;
}

/* Conta quantas posições existem no caminho encontrado. */
int qtd_posicoes(Labirinto* pilha){
    if(pilha == NULL) return 0;

    int qtd = 0;
    Labirinto atual = *pilha;
    while(atual != NULL){
        qtd++;
        atual = atual->prox;
    }
    return qtd;
}

int pilha_vazia(Labirinto* pilha){
    return pilha == NULL || *pilha == NULL;
}

/*
    Função auxiliar recursiva para gravar o caminho na ordem correta.
    Como a pilha guarda o último passo no topo, a recursão permite imprimir
    do início até a saída.
*/
static void grava_caminho_recursivo(Labirinto no, FILE* arquivo){
    if(no == NULL) return;
    grava_caminho_recursivo(no->prox, arquivo);
    fprintf(arquivo, "X=%d, Y=%d\n", no->player.posX, no->player.posY);
}

/* Grava o caminho encontrado no arquivo de saída. */
void grava_caminho_arquivo(Labirinto* pilha, FILE* arquivo){
    if(pilha == NULL || arquivo == NULL) return;
    grava_caminho_recursivo(*pilha, arquivo);
}

/*
    Carrega o labirinto a partir de um arquivo .txt.
    A primeira linha deve conter as dimensões, por exemplo: 30x10.
    Depois, o restante do arquivo representa o mapa do labirinto.
*/
int carrega_labirinto(char labirinto[MAX_LAB], int* linhas, int* colunas, const char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("ERRO: nao foi possivel abrir o arquivo %s\n", nome_arquivo);
        return 0;
    }

    int largura = 0;
    int altura = 0;

    if(fscanf(arquivo, "%dx%d\n", &largura, &altura) != 2){
        printf("ERRO: dimensoes invalidas no arquivo do labirinto. Use exemplo: 30x10\n");
        fclose(arquivo);
        return 0;
    }

    if(largura <= 0 || altura <= 0 || largura > 40 || altura > 40){
        printf("ERRO: o labirinto deve ter no maximo 40x40.\n");
        fclose(arquivo);
        return 0;
    }

    *colunas = largura;
    *linhas = altura;

    char linha[100];
    int pos = 0;

    /*
        Copia cada caractere do arquivo para o vetor unidimensional.
        Mesmo sendo visualmente um mapa em linhas e colunas, internamente
        ele é tratado como um único vetor.
    */
    for(int y = 0; y < *linhas; y++){
        if(fgets(linha, sizeof(linha), arquivo) == NULL){
            printf("ERRO: faltam linhas no arquivo do labirinto.\n");
            fclose(arquivo);
            return 0;
        }

        int tamanho = strlen(linha);
        if(tamanho > 0 && linha[tamanho - 1] == '\n'){
            linha[tamanho - 1] = '\0';
        }

        for(int x = 0; x < *colunas; x++){
            labirinto[pos++] = linha[x];
        }
    }

    fclose(arquivo);
    return 1;
}

/* Procura um símbolo no labirinto, como P para início ou S para saída. */
Personagem encontra_personagem(char labirinto[MAX_LAB], int linhas, int colunas, char simbolo){
    Personagem p = {0, 0};

    for(int i = 0; i < linhas * colunas; i++){
        if(labirinto[i] == simbolo){
            p.posY = (i / colunas) + 1;
            p.posX = (i % colunas) + 1;
            return p;
        }
    }

    return p;
}

/* Converte uma posição X/Y em índice do vetor unidimensional. */
int pos_2d_para_linear(int x, int y, int colunas){
    return (y - 1) * colunas + (x - 1);
}

/*
    Verifica se o personagem pode andar para determinada posição.
    Ele não pode sair dos limites, atravessar paredes ou voltar para uma casa já visitada.
*/
int pode_mover(char labirinto[MAX_LAB], int x, int y, int colunas, int linhas, char visitados[MAX_LAB]){
    if(x < 1 || x > colunas || y < 1 || y > linhas) return 0;

    int pos = pos_2d_para_linear(x, y, colunas);

    if(labirinto[pos] == '#') return 0;
    if(visitados[pos] == 'V') return 0;

    return 1;
}

/*
    Algoritmo principal de busca usando backtracking.
    A função tenta andar pelo labirinto até encontrar a saída. Caso um caminho
    não funcione, ela volta removendo a posição da pilha e tenta outra direção.
*/
int backtracking(Personagem atual, Personagem saida, char labirinto[MAX_LAB], char visitados[MAX_LAB], Labirinto* caminho, int colunas, int linhas, Mochila* mochila){
    int pos = pos_2d_para_linear(atual.posX, atual.posY, colunas);

    visitados[pos] = 'V';
    insere_posicao(caminho, atual);

    /* Exibe a movimentação do personagem e o conteúdo atual da mochila. */
    imprime_labirinto(labirinto, linhas, colunas, atual);
    exibe_elementos_mochila(mochila);
    Sleep(100);

    /* Caso base da recursão: chegou na saída. */
    if(atual.posX == saida.posX && atual.posY == saida.posY){
        return 1;
    }

    /* Vetores usados para tentar os movimentos: cima, direita, baixo e esquerda. */
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    for(int i = 0; i < 4; i++){
        int novo_x = atual.posX + dx[i];
        int novo_y = atual.posY + dy[i];

        if(pode_mover(labirinto, novo_x, novo_y, colunas, linhas, visitados)){
            int nova_pos = pos_2d_para_linear(novo_x, novo_y, colunas);
            char elemento = labirinto[nova_pos];

            /*
                Tratamento dos elementos especiais:
                T sorteia e adiciona um tesouro;
                A remove o primeiro tesouro da mochila, se existir.
            */
            if(elemento == 'T'){
                int valor = (rand() % 100) + 1;
                printf("Tesouro encontrado: %d moedas\n", valor);
                insere_mochila_ordenado(mochila, valor);
            }
            else if(elemento == 'A'){
                printf("Armadilha encontrada! Perdendo o menor tesouro...\n");
                remove_inicio_mochila(mochila);
            }

            Personagem proximo = {novo_x, novo_y};
            if(backtracking(proximo, saida, labirinto, visitados, caminho, colunas, linhas, mochila)){
                return 1;
            }
        }
    }

    /* Se nenhuma direção deu certo, remove a posição atual e volta uma etapa. */
    remove_posicao(caminho);
    return 0;
}

/*
    Imprime o labirinto no console.
    A posição atual do personagem é mostrada com P durante a movimentação.
*/
void imprime_labirinto(char labirinto[MAX_LAB], int linhas, int colunas, Personagem atual){
    limpa_tela();
    printf("=== LABIRINTO DE DADOS ===\n\n");

    for(int y = 1; y <= linhas; y++){
        for(int x = 1; x <= colunas; x++){
            int pos = pos_2d_para_linear(x, y, colunas);
            if(x == atual.posX && y == atual.posY){
                printf("P");
            }
            else if(labirinto[pos] == 'P'){
                printf(" ");
            }
            else{
                printf("%c", labirinto[pos]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
