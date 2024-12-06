#include <stdio.h>
#include <stdlib.h>

typedef struct celula{
    int carta;
    struct celula *prox;
} celula;

// a função empilha adiciona uma carta na base
void empilha(celula **base, int carta_nova){
    celula *novo = malloc(sizeof(celula));
    if(novo != NULL){
        novo->carta = carta_nova;
        if(*base != NULL){ // fila com itens
            novo->prox = *base;
            *base = novo;
        }
        else{ // fila vazia
            novo->prox = NULL;
            *base = novo;
        }
    }
    else
        printf("Erro ao alocar memória.\n");
}

int descarta_carta(celula **base){
    int c = 0;
    if(*base != NULL){ // fila com pelo menos um item
        celula *descarte = NULL;
        if((*base)->prox != NULL){ // fila com mais de um item
            celula *temp = *base;
            while(temp->prox->prox != NULL)
                temp = temp->prox; // temp nesse caso será o penúltimo elemento
            descarte = temp->prox;
            temp->prox = NULL;
            c = descarte->carta;
            free(descarte);
        }
        else{ // fila com um item
            descarte = *base;
            *base = NULL;
            c = descarte->carta;
            free(descarte);
        }
    }
    else
        printf("A fila esta vazia.\n");
    return c;
}

void joga_carta_pra_base(celula **base){
    if(*base != NULL){
        celula *temp = *base; // o ponteiro temp aponta para a carta do topo, ou o último elemento da fila(a partir da base)
        while(temp->prox != NULL)
            temp = temp->prox;
        empilha(base, temp->carta);
        descarta_carta(base);
    }
}

int main(){
    int num_cartas = 1;

    while(num_cartas != 0){
        scanf("%d", &num_cartas);

        if(num_cartas <= 0)
            break;
        else{
            celula *base_teste = NULL;
            int *cartas_descartadas = malloc((num_cartas - 1)*sizeof(int)), cont = 0;

            for(int i = 0; i < num_cartas; i++)
                empilha(&base_teste, i+1);

            while(base_teste->prox != NULL){
                cartas_descartadas[cont++] = descarta_carta(&base_teste);
                joga_carta_pra_base(&base_teste);
            }

            printf("Discarded cards: ");
            for(int i = 0; i < num_cartas - 1; i++){
                if(i != num_cartas - 2)
                    printf("%i, ", cartas_descartadas[i]);
                else
                    printf("%i\n", cartas_descartadas[i]);
            }

            printf("Remaining card: %i\n", base_teste->carta);
            free(cartas_descartadas);
            free(base_teste);
        }
    }
    return 0;
}
