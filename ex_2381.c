#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxcarac 20

void ordena_lista(char lista[][maxcarac], int n){
    char aux[maxcarac];
    if(n > 1){
        for(int i = 0; i < n - 1; i++){
            for(int j = 0; j < n - 1; j++){
                int t = strcmp(lista[j], lista[j+1]);
                if(t > 0){
                    // invertendo posições
                    strcpy(aux, lista[j]);
                    strcpy(lista[j], lista[j+1]);
                    strcpy(lista[j+1], aux);
                }
            }
        }
    }
}

int main(){
    int N, k;
    scanf("%d %d", &N, &k);

    getchar();

    char lista_alunos[N][maxcarac];
    for(int i = 0; i < N; i++){
        do{
            fgets(lista_alunos[i], maxcarac, stdin);
            lista_alunos[i][strcspn(lista_alunos[i], "\n")] = '\0';  // Remove o '\n' extra
        } while(strlen(lista_alunos[i]) == 0);
    }

    ordena_lista(lista_alunos, N);

    printf("%s\n", lista_alunos[k-1]);

    return 0;
}
