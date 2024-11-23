#include <stdio.h>
#include <string.h>

#define maxcarac 1000

int verif_expressao(char expressao[]){
    int topo = 0;
    for(int i = 0; expressao[i] != '\0'; i++){
        if(expressao[i] == '(')
            topo++; //empilha
        else if(expressao[i] == ')'){
            if(topo == 0)
                return 0; //mal formada
            --topo; //desempilha
        }
    }
    if(topo != 0) 
        return 0; //mal formada
    else
        return 1; //bem formada
}

int main(){
    char expressao[maxcarac];
    while(fgets(expressao, maxcarac, stdin) != NULL){
        if(verif_expressao(expressao) == 0)
            printf("incorrect\n");
        else
            printf("correct\n");
    }
    
    return 0;
}
