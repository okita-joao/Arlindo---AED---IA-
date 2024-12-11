#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int separa(int p, int r, int v[]){
    int c = v[r], j = p, t;
    for(int k = p; k < r; k++){
        if(v[k] <= c){
            t = v[j];
            v[j] = v[k];
            v[k] = t;
            j++;
        }
    }
    v[r] = v[j];
    v[j] = c;
    return j;
}

void quicksort(int p, int r, int v[]){
    int j;
    if(p < r){
        j = separa(p, r, v);
        quicksort(p, j-1, v);
        quicksort(j+1, r, v);
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

    // contagem do tempo do quicksort
    t1 = clock();
    quicksort(0, tam, vetor1);
    t1 = clock() - t1;

    printf("Tempo de execucao do Quick Sort: %lf ms\n\n", ((double)t1)/((CLOCKS_PER_SEC/1000)));

    return 0;
}
