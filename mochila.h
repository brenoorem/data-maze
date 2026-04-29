typedef struct tesouro* Mochila;

Mochila* cria_mochila();

void libera_mochila(Mochila* li);

int tamanho_mochila(Mochila* li);

int insere_mochila_ordenado(Mochila *li, int moedas);