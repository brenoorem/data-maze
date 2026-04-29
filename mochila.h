typedef struct tesouro* Mochila;

Mochila* cria_mochila();

void libera_mochila(Mochila* li);

int tamanho_mochila(Mochila* li);

int insere_mochila_ordenado(Mochila *li, int moedas);

int remove_inicio_mochila(Mochila *li);

int exibe_elementos_mochila(Mochila *li);