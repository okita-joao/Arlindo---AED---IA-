#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxcarac 500

// função para verificar se a expressão infixa está bem formada
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

void converte_posfixa(char expressao[]){
    int num_caracs = 0, topo_posfixa = 0, topo_operadores = 0, j, k;
    char *posfixa = malloc(maxcarac*sizeof(char)), *operadores = malloc(maxcarac*sizeof(char));
    while(expressao[num_caracs] != '\0')
        num_caracs++;
    for(int i = 0; i < num_caracs; i++){
        switch(expressao[i]){
            case '(':
                operadores[topo_operadores++] = '('; // empilha operadores
                break;

            case '^':
                operadores[topo_operadores++] = '^'; // empilha operadores
                break;

            case '*':
                if(topo_operadores > 0){ // pilha operadores abastecida
                    if(operadores[topo_operadores - 1] == '+' || operadores[topo_operadores - 1] == '-' || operadores[topo_operadores - 1] == '(')
                        operadores[topo_operadores++] = '*'; // empilha operadores
                    else if(operadores[topo_operadores - 1] == '^' || operadores[topo_operadores - 1] == '/' || operadores[topo_operadores - 1] == '*'){
                        while(operadores[topo_operadores - 1] != '(' && topo_operadores > 0){
                            posfixa[topo_posfixa++] = operadores[topo_operadores - 1]; // empilha posfixa
                            operadores[--topo_operadores] = '\0'; // desempilha operadores
                        }
                        operadores[topo_operadores++] = '*';
                    }
                }
                else // pilha operadores vazia
                    operadores[topo_operadores++] = '*'; // empilha operadores
                break;

            case '/':
                if(topo_operadores > 0){ // pilha operadores abastecida
                    if(operadores[topo_operadores - 1] == '+' || operadores[topo_operadores - 1] == '-' || operadores[topo_operadores - 1] == '(')
                        operadores[topo_operadores++] = '/'; // empilha operadores
                    else if(operadores[topo_operadores - 1] == '^' || operadores[topo_operadores - 1] == '/' || operadores[topo_operadores - 1] == '*'){
                        while(operadores[topo_operadores - 1] != '(' && topo_operadores > 0){
                            posfixa[topo_posfixa++] = operadores[topo_operadores - 1]; // empilha posfixa
                            operadores[--topo_operadores] = '\0'; // desempilha operadores
                        }
                        operadores[topo_operadores++] = '/';
                    }
                }
                else // pilha operadores vazia
                    operadores[topo_operadores++] = '/'; // empilha operadores
                break;

            case '+':
                if(topo_operadores > 0){ // pilha operadores abestecida
                    while(operadores[topo_operadores - 1] != '(' && topo_operadores > 0){
                            posfixa[topo_posfixa++] = operadores[topo_operadores - 1]; // empilha posfixa
                            operadores[--topo_operadores] = '\0'; // desempilha operadores
                        }
                    operadores[topo_operadores++] = '+';
                }
                else // pilha operadores vazia
                    operadores[topo_operadores++] = '+'; // empilha operadores
                break;

            case '-':
                if(topo_operadores > 0){ // pilha operadores abestecida
                    while(operadores[topo_operadores - 1] != '(' && topo_operadores > 0){
                            posfixa[topo_posfixa++] = operadores[topo_operadores - 1]; // empilha posfixa
                            operadores[--topo_operadores] = '\0'; // desempilha operadores
                        }
                    operadores[topo_operadores++] = '-';
                }
                else // pilha operadores vazia
                    operadores[topo_operadores++] = '-'; // empilha operadores
                break;

            case ')':
                k = topo_operadores;
                operadores[topo_operadores++] = ')'; // empilha operadores
                j = topo_operadores - 1;
                while(operadores[j] != '(')
                    j--;
                for(int l = k; l > j; l--){
                    if(operadores[l] != ')')
                        posfixa[topo_posfixa++] = operadores[l]; // empilha posfixa
                }
                for(int l = k; l >= j; l--)
                    operadores[--topo_operadores] = '\0'; // desempilha operadores
                break;
            default: // caso seja operando(letra ou número)
                posfixa[topo_posfixa++] = expressao[i];
        }
    }
    // passo final
    for(int i = topo_operadores - 1; i >= 0; i--){
        posfixa[topo_posfixa++] = operadores[i]; // empilha posfixa
        operadores[--topo_operadores] = '\0'; // desempilha operadores
    }

    posfixa[topo_posfixa] = '\0'; // buffer da posfixa
    strcpy(expressao, posfixa);

    free(operadores);
    free(posfixa);
}

int main(){
    int expressoes;
    char expressao[maxcarac];

    scanf("%d", &expressoes);
    for(int i = 0; i < expressoes; i++){
        scanf("%499s", expressao);

        converte_posfixa(expressao);
        printf("%s\n", expressao);
    }

    return 0;
}
