#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion(int v[], int n){
    int x, i, j;
    for(j = 1; j < n; j++){
        x = v[j];
        for(i = j-1; i >= 0 && v[i] > x; i--)
            v[i+1] = v[i];
        v[i+1] = x;
    }
}

int main(){
    clock_t t1;
    int tam;

    srand(time(NULL));

    printf("tamanho do vetor: ");
    scanf("%d", &tam);

    int vetor1[tam];

    for(int i = 0; i < tam; i++)
        vetor1[i] = rand() % tam;

    // contagem do tempo do insertion
    t1 = clock();
    insertion(vetor1, tam);
    t1 = clock() - t1;

    printf("Tempo de execucao do Insertion Sort: %lf ms\n\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));

    return 0;
}
