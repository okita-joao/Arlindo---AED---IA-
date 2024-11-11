#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 1000
#define MAX_TAMANHO 21 // O tamanho máximo de cada item é 20, mais 1 para o caractere nulo

// Função para comparar strings, necessária para a ordenação com qsort
int comparar(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int N;  // Número de listas de compras
    scanf("%d", &N);
    getchar();  // Limpar o '\n' que fica no buffer após ler o inteiro N
    
    // Processar cada lista
    while (N--) {
        char *itens[MAX_ITENS];  // Array para armazenar os itens da lista
        int n_itens = 0;  // Contador para o número de itens únicos
        
        // Leitura da lista de compras
        char linha[10001];  // A linha pode ter até 1000 itens com até 20 caracteres
        fgets(linha, sizeof(linha), stdin);
        
        // Variáveis para armazenar a palavra atual e iniciar a separação
        char *item = strtok(linha, " \n");
        
        // Adiciona itens únicos na lista
        while (item != NULL) {
            // Verifica se o item já está na lista
            int encontrado = 0;
            for (int i = 0; i < n_itens; i++) {
                if (strcmp(itens[i], item) == 0) {
                    encontrado = 1;
                    break;
                }
            }
            
            // Se não foi encontrado, adiciona o item
            if (!encontrado) {
                itens[n_itens] = strdup(item);  // Aloca memória para o item e adiciona
                n_itens++;
            }
            
            // Proximo item
            item = strtok(NULL, " \n");
        }

        // Ordena os itens alfabeticamente
        qsort(itens, n_itens, sizeof(char *), comparar);

        // Imprime a lista sem duplicatas e ordenada
        for (int i = 0; i < n_itens; i++) {
            printf("%s", itens[i]);
            if (i < n_itens - 1) {
                printf(" ");
            }
            free(itens[i]);  // Libera a memória alocada para cada item
        }
        printf("\n");
    }

    return 0;
}
