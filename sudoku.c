/* 
  Nome: João Pedro Navarro Okita
  RA: 176530
  Exercício: 1383
  Data: 28/10/24
*/

#include <stdio.h>
#include <stdbool.h>

int verif_sol_sudoku(int tabela [9][9]);
int verif_linha(int tabela[9][9]);
int verif_coluna(int tabela[9][9]);
int verif_3x3_2(int tabela[3][3]);
int verif_3x3(int tabela[9][9]);

int main() {
    int n;
    scanf("%d", &n);
    for(int k = 0; k < n; k++){
        int sudoku[9][9];
        // preenchendo o sudoku
        for(int a = 0; a < 9; a++){
            for(int b = 0; b < 9; b++){
                scanf("%d", &sudoku[a][b]);
            }
        }
        //verificação sudoku
        int num = verif_sol_sudoku(sudoku);
        if(num == 1){
            printf("Instância %i\nNAO\n\n", (k+1));
        }
        if(num == 0){
            printf("Instância %i\nSIM\n\n", (k+1));
        }
    }
    return 0;
}

int verif_linha(int tabela[9][9]){
    // loop for para ver cada linha, a = linha, b = coluna
    for(int a = 0; a < 9; a++){
        //vetor de auxílio
        int lin[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        //contador
        int cont = 0;
        for(int b = 0; b < 9; b++){
            for(int c = 0; c < 9; c++){
                if(tabela[a][b] == lin[c]){
                    lin[c] = 0;
                }
            }
        }
        //loop for de verificação
        for(int d = 0; d < 9; d++){
            if(lin[d] != 0){
                cont++;
            }
        }
        if(cont != 0){
            return 1; //linha inválida
        }
    }
    return 0; //linhas todas válidas
}

int verif_coluna(int tabela[9][9]){
    //loop for para verificar cada coluna; b = col, a = lin
    for(int b = 0; b < 9; b++){
        //vetor de auxílio
        int col[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        //contador
        int cont = 0;
        for(int a = 0; a < 9; a++){
            for(int c = 0; c < 9; c++){
                if(tabela[a][b] == col[c]){
                    col[c] = 0;
                }
            }
        }
        //loop for de verificação da coluna
        for(int d = 0; d < 9; d++){
            if(col[d] != 0){
                cont++;
            }
        }
        if(cont != 0){
            return 1; //coluna inválida
        }
    }
    return 0; //colunas todas válidas
}

int verif_3x3_2(int tabela[3][3]) {
    bool numeros[10] = {false}; // vetor para marcar números de 1 a 9
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            int num = tabela[a][b];
            if (num < 1 || num > 9 || numeros[num]) {
                return 1; // 3x3 inválido
            }
            numeros[num] = true;
        }
    }
    return 0; // 3x3 válido
}

int verif_3x3(int tabela[9][9]) {
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            int subtab[3][3];
            for (int a = 0; a < 3; a++) {
                for (int b = 0; b < 3; b++) {
                    subtab[a][b] = tabela[i + a][j + b];
                }
            }
            if (verif_3x3_2(subtab) != 0) {
                return 1; // Região 3x3 inválida
            }
        }
    }
    return 0; // Todas as regiões 3x3 válidas
}


int verif_sol_sudoku(int tabela [9][9]){
    int cont = 0;
    if(verif_linha(tabela) != 0)
        cont++;
    if(verif_coluna(tabela) != 0)
        cont++;
    if(verif_3x3(tabela) != 0)
        cont++;
    if(cont != 0)
        return 1; // matriz incorreta
    if(cont == 0)
        return 0; // matriz correta
}