#include <stdio.h>
#include <stdlib.h>

int separa(int p, int r, int v[]){
    int c = v[r], j = p, t;
    for(int k = p; k < r; k++){
        if(v[k] >= c){
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
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        int M, cont = 0; // M é o número de alunos
        scanf("%d", &M);
        int *notas = malloc(M*sizeof(int)), *alunos = malloc(M*sizeof(int));
        for(int i = 0; i < M; i++){
            scanf("%d", &notas[i]);
            alunos[i] = notas[i];
        }

        quicksort(0, M-1, notas); // ordena as notas em ordem decrescente

        for(int i = 0; i < M; i++)
            if(alunos[i] == notas[i]) cont++;

        printf("%i\n", cont);

        free(notas);
        free(alunos);
    }

    return 0;
}
