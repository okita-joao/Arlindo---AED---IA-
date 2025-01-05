#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menor(int v[], int n){
    int menor = v[0];
    for(int i = 0; i < n; i++)
        if(v[i] < menor) menor = v[i];
    return menor;
}

int main(){
    int ops, topo = 0;
    scanf("%d", &ops);
    int *saco = malloc(ops*sizeof(int));
    if(saco == NULL){
        printf("Erro ao alocar memoria\n");
        return 0;
    }
    for(int i = 0; i < ops; i++){
        char comando[6];
        scanf("%s", comando);

        if(strcmp(comando, "MIN") == 0){
            if(topo == 0)
                printf("EMPTY\n");
            else
                printf("%i\n", menor(saco, topo));
        } else if(strcmp(comando, "POP") == 0){
            if(topo == 0)
                printf("EMPTY\n");
            else
                topo--;
        } else {
            int V;
            scanf("%d", &V);
            saco[topo++] = V;
        }
    }
    free(saco);
    return 0;
}
