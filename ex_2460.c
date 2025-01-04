#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa{
    int ident;
    struct pessoa *prox;
} pessoa;

void printf_fila(pessoa *base){
    pessoa *temp = base;
    if(temp){
        while(temp->prox != NULL){
            printf("%i ", temp->ident);
            temp = temp->prox;
        }
        printf("%i\n", temp->ident);
    }
    else
        printf("Lista vazia\n");
}

void empilha_fila(pessoa **base, int i){
    pessoa *nova = malloc(sizeof(pessoa));
    if(nova){
        nova->ident = i;
        nova->prox = NULL;
        if(*base == NULL)// fila vazia
            *base = nova;
        else{
            pessoa *temp = *base;
            while(temp->prox != NULL)
                temp = temp->prox;
            temp->prox = nova;
        }
    }
    else{
        printf("Erro ao alocar memória\n");
    }
}

void remove_pessoa_fila(pessoa **base, int i){
    pessoa *temp = *base, *anterior = NULL;
    if(*base != NULL){
        if(temp->ident == i){ // se for o primeiro elemento a ser eliminado
            *base = temp->prox;
            temp->prox = NULL;
            free(temp);
        }
        else{
            while(temp != NULL && temp->ident != i){
                anterior = temp;
                temp = temp->prox;
            }
            if(temp == NULL){
                printf("Erro: pessoa não encontrada\n");
                return;
            }
            anterior->prox = temp->prox;
            temp->prox = NULL;
            free(temp);
        }
    }
    else
        printf("Lista já vazia\n");
}

int main(){
    pessoa *fila = NULL;
    int num_pessoas, num_pessoas_sairam;
    scanf("%d", &num_pessoas);
    int *identificadores = malloc(num_pessoas*sizeof(int));
    if(identificadores == NULL){
        printf("Erro ao alocar memória\n");
        return 0;
    }
    for(int i = 0; i < num_pessoas; i++){
        scanf("%d", &identificadores[i]);
        empilha_fila(&fila, identificadores[i]);
    }
    scanf("%d", &num_pessoas_sairam);
    int *ident_saidos = malloc(num_pessoas_sairam*sizeof(int));
    if(ident_saidos == NULL){
        printf("Erro ao alocar memória\n");
        return 0;
    }
    for(int i = 0; i < num_pessoas_sairam; i++){
        scanf("%d", &ident_saidos[i]);
        remove_pessoa_fila(&fila, ident_saidos[i]);
    }
    printf_fila(fila);
    return 0;
}
