#include <stdio.h>

#define MAX 1000

typedef struct {
    char dados[MAX];
    int topo;
} Pilha;

void inicializaPilha(Pilha* p) {
    p->topo = -1;
}

int pilhaVazia(Pilha* p) {
    return p->topo == -1;
}

void empilha(Pilha* p, char valor) {
    p->dados[++(p->topo)] = valor;
}

char desempilha(Pilha* p) {
    if (!pilhaVazia(p)) {
        return p->dados[(p->topo)--];
    }
    return '\0'; // Retorna um valor nulo se a pilha estiver vazia
}

int main() {
    int n, i, j;
    char entrada[MAX], saida[MAX];
    Pilha pilha;

    while (scanf("%d", &n) && n) {
        for (i = 0; i < n; i++) 
            scanf(" %c", &entrada[i]);
        for (i = 0; i < n; i++) 
            scanf(" %c", &saida[i]);
        
        entrada[n] = saida[n] = '\0';

        inicializaPilha(&pilha);
        
        i = j = 0;
        while (1) {
            if (!pilhaVazia(&pilha) && j < n && pilha.dados[pilha.topo] == saida[j]) {
                desempilha(&pilha);
                printf("R");
                j++;
            } else if (i < n) {
                empilha(&pilha, entrada[i]);
                printf("I");
                i++;
            } else {
                break;                    
            }
        }
        
        if (pilhaVazia(&pilha)) 
            printf("\n");
        else  
            printf(" Impossible\n");

        // Limpar a pilha
        while (!pilhaVazia(&pilha)) {
            desempilha(&pilha);
        }
    }

    return 0;
}
