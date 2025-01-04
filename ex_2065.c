#include <stdio.h>
#include <stdlib.h>

typedef struct caixa{
    int i;
    int demora;
    int qnd_sai;
    struct caixa *prox;
} caixa;

typedef struct cliente{
    int produtos;
    struct cliente *prox;
} cliente;

int menor_i(caixa *base){
    caixa *temp = base;
    int menor = temp->i;
    while(temp != NULL){
        if(temp->i < menor) 
            menor = temp->i;
        temp = temp->prox;
    }
    return menor;
}

int busca_tempo_dmr(caixa *base, int ident){
    caixa *temp = base;
    while(temp != NULL && temp->i != ident)
        temp = temp->prox;
    if(temp == NULL) return -1;
    return temp->demora;
}

void empilha_cliente(cliente **base, int prods){
    cliente *novo = malloc(sizeof(cliente));
    if(novo){
        novo->produtos = prods;
        novo->prox = NULL;
        if(*base){
            cliente *temp = *base;
            while(temp->prox != NULL)
                temp = temp->prox;
            temp->prox = novo;
        }
        else{
            *base = novo;
        }
    }
    else
        printf("Erro ao alocar memoria\n");
}

int desempilha_cliente(cliente **base){
    if (*base == NULL) return -1; // Lista vazia
    int p;
    cliente *temp = *base;
    *base = temp->prox;
    temp->prox = NULL;
    p = temp->produtos;
    free(temp);
    return p;
}

void empilha_caixa(caixa **base, int t, int t2, int t3){
    caixa *novo = malloc(sizeof(caixa));
    if(novo){
        novo->demora = t;
        novo->qnd_sai = t2;
        novo->i = t3;
        novo->prox = NULL;
        if(*base){
            caixa *temp = *base;
            while(temp->prox != NULL)
                temp = temp->prox;
            temp->prox = novo;
        }
        else{
            *base = novo;
        }
    }
    else
        printf("Erro ao alocar memoria\n");
}

void desempilha_caixa(caixa **base){
    caixa *temp = *base;
    *base = temp->prox;
    temp->prox = NULL;
    free(temp);
}

void desempilha_caixa_especifico(caixa **base, int ident){
    if(*base == NULL) return; // Lista vazia
    caixa *temp = *base, *anterior = NULL;
    while(temp != NULL && temp->i != ident) {
        anterior = temp;
        temp = temp->prox;
    }
    if(temp == NULL) return; // Caixa não encontrado
    if(anterior == NULL)
        *base = temp->prox; // Remove o primeiro elemento
    else
        anterior->prox = temp->prox; // Remove elemento intermediário ou final
    temp->prox = NULL;
    free(temp);
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int *temp_dmr_empregados = malloc(N*sizeof(int)), *prods_clientes = malloc(M*sizeof(int));
    if(temp_dmr_empregados == NULL || prods_clientes == NULL){
        printf("Erro ao alocar memoria\n");
        return 0;
    }

    // FUNCIONÁRIOS
    for(int i = 0; i < N; i++)
        scanf("%d", &temp_dmr_empregados[i]);

    // CLIENTES 
    for(int i = 0; i < M; i++)
        scanf("%d", &prods_clientes[i]);
    
    // LISTA CLIENTES
    cliente *clientes = NULL;
    for(int i = 0; i < M; i++)
        empilha_cliente(&clientes, prods_clientes[i]);

    // LISTA FUNCIONÁRIOS
    caixa *disponiveis = NULL, *ocupados = NULL;
    for(int i = 0; i < N; i++)
        empilha_caixa(&disponiveis, temp_dmr_empregados[i], 0, i+1);

    int tempo = 0;
    while(clientes != NULL){
        // (1) checar se tem caixas disponíveis e mover os clientes para eles
        while(disponiveis != NULL && clientes != NULL){
                int p = menor_i(disponiveis);
                int v = busca_tempo_dmr(disponiveis, p);
                if(v == -1) break; // caixa não encontrado
                empilha_caixa(&ocupados, v, v*desempilha_cliente(&clientes) + tempo, p);
                desempilha_caixa_especifico(&disponiveis, p);
        }
        // (2) verificar se já está na hora de algum dos caixas voltarem
        caixa *temp = ocupados;
        int k = 0;
        while(temp != NULL){
            if(temp->qnd_sai == tempo){
                caixa *next = temp->prox;
                empilha_caixa(&disponiveis, temp->demora, 0, temp->i);
                desempilha_caixa_especifico(&ocupados, temp->i);
                temp = next;
                k++;
            }
            else
                temp = temp->prox;
        }
        if(k != 0){
            tempo--;
            k = 0;
        }
        tempo++;
    }
    // (3) pegando o maior tempo restante
    if(ocupados != NULL){
        caixa *temp = ocupados;
        int maior_tempo = temp->qnd_sai;
        while(temp != NULL){
            if(temp->qnd_sai > maior_tempo)
                maior_tempo = temp->qnd_sai;
            temp = temp->prox;
        }
        printf("%i\n", maior_tempo);
    }
    else
        printf("%i\n", tempo);

    free(temp_dmr_empregados);
    free(prods_clientes);
    return 0;
}
