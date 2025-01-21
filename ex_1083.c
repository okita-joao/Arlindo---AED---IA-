#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 4000

// Definindo a estrutura de Pilha
typedef struct {
    char dados[MAX];
    int topo;
} Pilha;

void inicializaPilha(Pilha* p) {
    p->topo = -1;
}

bool pilhaVazia(Pilha* p) {
    return p->topo == -1;
}

void empilha(Pilha* p, char valor) {
    p->dados[++(p->topo)] = valor;
}

char desempilha(Pilha* p) {
    if (!pilhaVazia(p)) {
        return p->dados[(p->topo)--];
    }
    return '\0'; // Retorna um valor nulo se a pilha estiver vazia
}

bool isOp(char a) {
    return a == '+' || a == '-' || a == '*' || a == '/' || a == '^' || a == '>' || a == '<' || a == '=' || a == '#' || a == '.' || a == '|';
}

bool isCa(char a) {
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9');
}

void add(char* bizarro, char a) {
    int len = strlen(bizarro);
    bizarro[len] = a;
    bizarro[len + 1] = '\0';
}

int main() {
    int len;
    int precedence[256] = {0}; // Precedência de operadores
    precedence['|'] = 1;
    precedence['.'] = 2;
    precedence['>'] = precedence['<'] = precedence['='] = precedence['#'] = 3;
    precedence['+'] = precedence['-'] = 4;
    precedence['*'] = precedence['/'] = 5;
    precedence['^'] = 6;

    char polish[MAX], bizarro[MAX];
    while (scanf("%s", polish) != EOF) {
        len = strlen(polish);
        Pilha pilha;
        inicializaPilha(&pilha);

        bool lex = false, syn = false;
        strcpy(bizarro, "");

        for (int i = 0; i < len && !lex; i++) {
            if (isOp(polish[i])) {
                if (i + 1 == len || i == 0) syn = true;
                else if (!isCa(polish[i - 1]) && polish[i - 1] != ')') syn = true;
                else if (!isCa(polish[i + 1]) && polish[i + 1] != '(') syn = true;
                
                while (!pilhaVazia(&pilha) && pilha.dados[pilha.topo] != '(' && precedence[pilha.dados[pilha.topo]] >= precedence[polish[i]]) {
                    add(bizarro, desempilha(&pilha));
                }
                empilha(&pilha, polish[i]);
            }
            else if (polish[i] == '(') {
                if (i > 0 && (isCa(polish[i - 1])) || polish[i - 1] == ')') syn = true;
                empilha(&pilha, '(');
            }
            else if (polish[i] == ')') {
                if (i > 0 && polish[i - 1] == '(') syn = true;
                if (pilhaVazia(&pilha)) {
                    syn = true;
                }
                while (!pilhaVazia(&pilha) && pilha.dados[pilha.topo] != '(') {
                    add(bizarro, desempilha(&pilha));
                    if (pilhaVazia(&pilha)) {
                        syn = true;
                        break;
                    }
                }
                if (!pilhaVazia(&pilha)) desempilha(&pilha);
            }
            else if ((polish[i] >= 'a' && polish[i] <= 'z') || (polish[i] >= 'A' && polish[i] <= 'Z')) {
                if (i == 0) add(bizarro, polish[i]);
                else if (isOp(polish[i - 1]) || polish[i - 1] == '(') add(bizarro, polish[i]);
                else syn = true;
            }
            else if (polish[i] >= '0' && polish[i] <= '9') {
                if (i == 0) add(bizarro, polish[i]);
                else if (isOp(polish[i - 1]) || polish[i - 1] == '(' || (polish[i - 1] >= '0' && polish[i - 1] <= '9')) add(bizarro, polish[i]);
                else syn = true;
            }
            else lex = true;
        }

        while (!lex && !syn && !pilhaVazia(&pilha)) {
            if (pilha.dados[pilha.topo] == '(') {
                syn = true;
                break;
            }
            add(bizarro, desempilha(&pilha));
        }

        if (lex) printf("Lexical Error!\n");
        else if (syn) printf("Syntax Error!\n");
        else printf("%s\n", bizarro);
    }

    return 0;
}
