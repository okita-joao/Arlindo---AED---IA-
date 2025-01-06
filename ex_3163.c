#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int acha_maior(int v[], int n){
    int maior = v[0];
    for(int i = 0; i < n; i++)
        if(v[i] > maior) maior = v[i];
    return maior;
}

// (-4 representa o lado leste, -3 o lado norte, -2 lado sul e -1 lado oeste)

int main(){
    
    int **matriz_avioes = malloc(4*sizeof(int *)); // vetor de ponteiros, esses ponteiros apontam para vetores de inteiros, por isso uma "matriz"
    if (matriz_avioes == NULL) {
        printf("Falha na alocação de memória para as linhas.\n");
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        matriz_avioes[i] = malloc(1000*sizeof(int));
        if (matriz_avioes[i] == NULL) {
            printf("Falha na alocação de memória para a linha %d.\n", i);
            return 1;
        }
    }

    // matriz_direções[0] = oeste
    // matriz_direções[1] = sul
    // matriz_direções[2] = norte
    // matriz_direções[3] = leste

    char comando = '\0';
    // contadores
    int N = 0, S = 0, L = 0, O = 0;

    while(comando != '0'){
        int num, direcao;
        scanf(" %c", &comando);
        if(comando == '0')
            break;
        scanf("%d", &num);
        
        // mudança de direção (comando = "-")
        if(comando == '-')
            direcao = num-1;
        
        // leitura dos aviões
        else if(comando == 'A'){
            int *t;
            switch(direcao){
                case 0:
                    t = &O;
                    break;
                case 1:
                    t = &S;
                    break;
                case 2:
                    t = &N;
                    break;
                case 3:
                    t = &L;
                    break;
            }
            matriz_avioes[direcao][*t] = num;
            *t += 1;
        }
    }

    // Ordenação
    int *vetor_sol = malloc((N+S+L+O)*sizeof(int));
    if(vetor_sol == NULL){
        printf("Erro ao alocar memória para o vetor solução\n");
        return 0;
    }

    int *maior = malloc(4*sizeof(int));
    if(maior == NULL){
        printf("Erro ao alocar memória para o vetor 'maior'\n");
        return 0;
    }
    maior[0] = N; maior[1] = S; maior[2] = L; maior[3] = O;
    int reps = acha_maior(maior, 4);
    free(maior);

    int t2 = 0; // contadores
    for(int t1 = 0; t1 < reps; t1++){
        if(t1 < O)
            vetor_sol[t2++] = matriz_avioes[0][t1];
        if(t1 < N)
            vetor_sol[t2++] = matriz_avioes[2][t1];
        if(t1 < S)
            vetor_sol[t2++] = matriz_avioes[1][t1];
        if(t1 < L)
            vetor_sol[t2++] = matriz_avioes[3][t1];
    }

    for(int i = 0; i < (N+S+L+O)-1; i++)
        printf("A%i ", vetor_sol[i]);
    printf("A%i\n", vetor_sol[(N+S+L+O)-1]);

    // Liberação de memória
    for (int i = 0; i < 4; i++) 
        free(matriz_avioes[i]);  // Libera cada linha
    free(matriz_avioes);  // Libera o vetor de ponteiros

    free(vetor_sol);

    return 0;
}
