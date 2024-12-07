#include <stdio.h>
#include <stdlib.h>

// FUNÇÕES AUXILIARES
int busca(int v[], int n, int x){
    for(int i = 0; i < n; i++)
        if(v[i] == x) return 1; // achou x no vetor
    return -1; // não achou x no vetor
}

int busca_index(int v[], int n, int x){
    for(int i = 0; i < n; i++){
        if(v[i] == x)
            return i+1;
    }
    return -1;
}

int verif_maior(int v[], int num_elementos){
    int maior = 0;
    for(int i = 0; i < num_elementos; i++)
        if(v[i] >= maior) maior = v[i];
    return maior;
}

// FUNÇÕES FILA
typedef struct vaga{
    int num_motorista;
    struct vaga *prox;
} vaga;

void entra_carro(vaga **entrada, int num){
    vaga *novo_motorista = malloc(sizeof(vaga));
    if(novo_motorista != NULL){
        novo_motorista->num_motorista = num;
        if(*entrada != NULL){ // tem pelo menos um elemento na fila
            novo_motorista->prox = *entrada;
            *entrada = novo_motorista;
        }
        else{
            *entrada = novo_motorista;
            novo_motorista->prox = NULL;
        }
    }
    else
        printf("Erro ao alocar memória.\n");
}

void sai_carro(vaga **entrada){
    if(*entrada != NULL){
        vaga *descarte = *entrada;
        *entrada = (*entrada)->prox;
        free(descarte);
    }
    else
        printf("A fila de carros já está vazia.\n");
}

int cont_carros(vaga *entrada){
    int c = 0;
    vaga *temp = entrada;
    while(temp != NULL){
        c++; 
        temp = temp-> prox;
    }
    return c;
}

// FUNÇÃO PRINCIPAL
int main(){
    int N = 1, K = 1;
    vaga *entrada = NULL;

    while(N != 0 && K != 0){
        printf("Digite N e K: ");
        scanf("%d %d", &N, &K);
        if(N != 0 && K != 0){
            int *horarios_entrada = malloc(N*sizeof(int)), *horarios_saida = malloc(N*sizeof(int)), l = 0;

            printf("Digite os horarios de entrada e saida de cada motorista:\n");
            for(int i = 0; i < N; i++){
                int ent, sai;
                scanf("%d %d", &ent, &sai);
                horarios_entrada[i] = ent;
                horarios_saida[i] = sai;
            }

            int i = 1; // i é o index/identificação do motorista. Assim vamos ter o motrista 1, ..., motorista N.
            for(int t = 1; t <= verif_maior(horarios_saida, N); t++){
                // entra 1 carro no tempo t
                if(busca(horarios_entrada, N, t) == 1 && busca(horarios_saida, N, t) == -1){
                    entra_carro(&entrada, i);
                    if(cont_carros(entrada) > K){
                        printf("Não\n");
                        l = 1;
                        break;
                    }
                    i++;
                }
                // sai 1 carro no tempo t
                else if(busca(horarios_entrada, N, t) == -1 && busca(horarios_saida, N, t) == 1){
                    if(entrada->num_motorista == busca_index(horarios_saida, N, t))
                        sai_carro(&entrada);
                    else{
                        printf("Não\n");
                        l = 1;
                        break;
                    }
                }
                // sai um 1 carro e entra 1 carro no tempo t
                else if(busca(horarios_entrada, N, t) == 1 && busca(horarios_saida, N, t) == 1){
                    if(entrada->num_motorista == busca_index(horarios_saida, N, t))
                        sai_carro(&entrada);
                    else{
                        printf("Não\n");
                        l = 1;
                        break;
                    }
                    entra_carro(&entrada, i);
                    i++;
                }
            }

            free(horarios_entrada);
            free(horarios_saida);

            // esvazia a fila
            while(entrada != NULL)
                sai_carro(&entrada);
            
            if(l == 0)
                printf("Sim\n");
        }
    }

    return 0;
}
