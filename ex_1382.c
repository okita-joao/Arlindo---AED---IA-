#include <stdio.h>
#include <stdlib.h>

#define MAXV 10100

int number[MAXV], posicao[MAXV];

int main() {
    int m, n, a;
    scanf("%d", &m);
    while (m--) {
        int qtd = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            number[i] = a - 1;
            posicao[a - 1] = i;
        }
        for (int i = 0; i < n; i++) {
            if (number[i] != i) {
                number[posicao[i]] = number[i];
                posicao[number[i]] = posicao[i];
                number[i] = posicao[i] = i;
                qtd++;
            }
        }
        printf("%d\n", qtd);
    }
    return 0;
}
