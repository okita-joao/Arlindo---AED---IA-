#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxcarac 1000

int cont_diamonds(char entrada[]){
    int topo = 0, diamonds = 0;
    for(int i = 0; entrada[i] != '\0'; i++){
        switch(entrada[i]){
        case '<':
            topo++; //empilha
            break;
        case '>':
            if(topo > 0){
                --topo; //desempilha
                diamonds++;
            }
            break;
        }
    }
    return diamonds;
}

int main(){
    int n;
    do{
        scanf("%d\n", &n);
    } while(n <= 0);

    char entrada[maxcarac];
    for(int i = 0; i < n; i++){
        fgets(entrada, maxcarac, stdin);
        if(entrada != NULL)
            printf("%i\n", cont_diamonds(entrada));
    }

    return 0;
}
