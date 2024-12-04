#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 20

void insertion(int v[TAM], int n){
    int x, i, j;
    for(j = 1; j < n; j++){
        x = v[j];
        for(i = j-1; i >= 0 && v[i] > x; i--)
            v[i+1] = v[i];
        v[i+1] = x;
    }
}

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
    clock_t t1, t2;
    int vetor1[TAM], vetor2[TAM];
    
    srand(time(NULL));

    for(int i = 0; i < TAM; i++)
        vetor1[i] = rand() % TAM;

    for(int i = 0; i < TAM; i++)
        vetor2[i] = rand() % TAM;


    // contagem do tempo do insertion
    t1 = clock();
    insertion(vetor1, TAM);
    t1 = clock() - t1;

    // contagem do tempo merge
    t2 = clock();
    merge(0, TAM, vetor2);
    t2 = clock() - t2;

    printf("Tempo de execucao do Insertion Sort: %lf ms\n\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));

    printf("Tempo de execucao do Merge Sort: %lf ms\n\n", ((double)t2)/((CLOCKS_PER_SEC/1000)));

    return 0;
}
