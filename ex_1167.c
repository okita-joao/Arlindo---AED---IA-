#include <stdio.h>
#include <string.h>

struct no {
    int prev, next, num;
    char nome[60];
};

struct no summer[110];

int main() {
    int i, n;
    while (scanf("%d", &n) && n) {
        // Lê o primeiro elemento
        scanf(" %s %d", summer[0].nome, &summer[0].num);
        
        // Inicializa os elementos de início e fim
        if (n > 1) {
            summer[0].prev = n - 1;
            summer[0].next = 1;
            summer[n - 1].prev = n - 2;
            summer[n - 1].next = 0;
        } else {
            summer[0].prev = summer[0].next = 0;
        }

        // Preenche os elementos intermediários
        for (i = 1; i < n - 1; ++i) {
            scanf(" %s %d", summer[i].nome, &summer[i].num);
            summer[i].prev = i - 1;
            summer[i].next = i + 1;
        }

        // Lê o último elemento se n > 1
        if (n > 1) {
            scanf(" %s %d", summer[n - 1].nome, &summer[n - 1].num);
        }

        int a = summer[0].num, c = 0, qtd = n;

        // Eliminação até restar um vencedor
        while (qtd != 1) {
            if (!(a & 1)) {  // Se 'a' for par, mover para o anterior
                for (i = 0; i < a; ++i) {
                    c = summer[c].prev;
                }
            } else {  // Se 'a' for ímpar, mover para o próximo
                for (i = 0; i < a; ++i) {
                    c = summer[c].next;
                }
            }

            a = summer[c].num;

            // Remove o elemento atual da lista
            summer[summer[c].prev].next = summer[c].next;
            summer[summer[c].next].prev = summer[c].prev;
            
            qtd--;
        }

        // Imprime o vencedor
        printf("Vencedor(a): %s\n", summer[summer[c].next].nome);
    }

    return 0;
}
