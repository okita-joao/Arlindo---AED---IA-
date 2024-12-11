#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void intercala(int p, int q, int r, int v[]){
    int i, j, k, *w;
    w = malloc((r-p)*sizeof(int));
    i = p; j = q; k = 0;
    while(i < q && j < r){
        if(v[i] <= v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }
    while(i < q)
        w[k++] = v[i++];
    while(j < r)
        w[k++] = v[j++];
    for(i = p; i < r; i++)
        v[i] = w[i-p];
    free(w);
}

void merge(int p, int r, int v[]){
    if(p < r-1){
        int q = (p + r)/2;
        merge(p, q, v);
        merge(q, r, v);
        intercala(p, q, r, v);
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

    // contagem do tempo do merge
    t1 = clock();
    merge(0, tam, vetor1);
    t1 = clock() - t1;

    printf("Tempo de execucao do Merge Sort: %lf ms\n\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));

    return 0;
}
