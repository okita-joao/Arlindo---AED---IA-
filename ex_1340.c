#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxoperacoes 2000

void insere_heap(int m, int v[]){
    int f = m;
    while(f > 1 && v[f/2] < v[f]){
        int aux = v[f/2];
        v[f/2] = v[f];
        v[f] = aux;
        f = f/2;
    }
}

void sacode_heap(int m, int v[]){
    if (m <= 0) return; // Heap vazio
    int aux, f = 2;
    while(f <= m){
        if(f < m && v[f] < v[f+1])
            f++;
        if(v[f/2] >= v[f]) 
            break;
        aux = v[f/2];
        v[f/2] = v[f];
        v[f] = aux;
        f *= 2;
    }
}

int pilha(int total[], int num_elementos){
    int *pilha_temp = malloc((num_elementos/2)*sizeof(int)), topo = 0;
    for(int i = 0; i < num_elementos; i++){
        if(i%2 == 0){
            switch(total[i]){
                case 1: // push
                    pilha_temp[topo++] = total[i+1];
                    break;
                case 2: // pop
                    if(topo > 0){
                        if(pilha_temp[topo-1] == total[i+1])
                            --topo;
                        else{
                            free(pilha_temp);
                            return 0; // não é pilha
                        }
                    }
                    else{ // pilha vazia
                        free(pilha_temp);
                        return 0; // não é pilha
                    }
                    break;
            }
        }
    }
    free(pilha_temp);
    return 1; // é pilha
}

int fila(int total[], int num_elementos){
    int *fila_temp = malloc((num_elementos/2)*sizeof(int)), topo = 0, inicio = 0;
    for(int i = 0; i < num_elementos; i++){
        if(i%2 == 0){
            switch(total[i]){
                case 1: // push
                    fila_temp[topo++] = total[i+1];
                    break;
                case 2: // pop
                    if(topo > inicio){
                        if(fila_temp[inicio] == total[i+1])
                            ++inicio;
                        else{
                            free(fila_temp);
                            return 0; // não é fila
                        }
                    }
                    else{
                        free(fila_temp);
                        return 0; // não é fila
                    }
                    break;
            }
        }
    }
    free(fila_temp);
    return 1; // é fila
}

int fila_prioridade(int total[], int num_elementos){
    int *fila_prioridade = malloc((num_elementos/2)*sizeof(int)), t = 0;
    fila_prioridade[0] = 0;
    for(int i = 0; i < num_elementos; i++){
        if(i%2 == 0){
            switch(total[i]){
                case 1: // push
                    fila_prioridade[++t] = total[i+1];
                    insere_heap(t, fila_prioridade);
                    break;
                case 2: // pop
                    if(fila_prioridade[1] != 0){ // tem coisa na fila
                        if(fila_prioridade[1] == total[i+1]){
                            fila_prioridade[1] = fila_prioridade[t--]; // ultimo termo da fila virá o primeiro
                            sacode_heap(t, fila_prioridade);
                        }
                        else{
                            free(fila_prioridade);
                            return 0; // não é fila de prioridade
                        }
                    }
                    else{
                        free(fila_prioridade);
                        return 0; // não é fila de prioridade
                    }    
                    break;
            }
        }
    }

    free(fila_prioridade);
    return 1; // é fila de prioridade
}

int main(){
    int operacoes, operacao, temp, *total = malloc((2*maxoperacoes)*sizeof(int)), j = 0;
    scanf("%d", &operacoes);

    for(int i = 0; i < operacoes; i++){
        scanf("%d %d", &operacao, &temp);
        switch(operacao){
            case 1:
                total[j++] = operacao;
                total[j++] = temp;
                break;
            case 2:
                total[j++] = operacao;
                total[j++] = temp;
                break;
        }
    }

    int eh_pilha = pilha(total, 2*operacoes);
    int eh_fila = fila(total, 2*operacoes);
    int eh_fila_prioridade = fila_prioridade(total, 2*operacoes);

    int soma = eh_pilha + eh_fila + eh_fila_prioridade;

    if(soma > 1) {
        printf("not sure\n");
    } else if(eh_pilha) {
        printf("stack\n");
    } else if(eh_fila) {
        printf("queue\n");
    } else if(eh_fila_prioridade) {
        printf("priority queue\n");
    } else {
        printf("impossible\n");
    }

    free(total);

    return 0;
}
