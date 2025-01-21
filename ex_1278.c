#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1000

int main() {
    int n, tam = 0;
    bool espaco = false;
    char linha[MAX_LEN], palavbra[MAX_LEN];

    scanf("%d", &n);
    while (n > 0) {
        getchar();
        char palavbras[n][MAX_LEN];
        for (int i = 0; i < n; i++) {
            palavbras[i][0] = '\0';
            fgets(linha, sizeof(linha), stdin);
            linha[strcspn(linha, "\n")] = '\0';

            char *token = strtok(linha, " ");
            while (token != NULL) {
                if (palavbras[i][0] == '\0') {
                    strcpy(palavbras[i], token);
                } else {
                    strcat(palavbras[i], " ");
                    strcat(palavbras[i], token);
                }
                token = strtok(NULL, " ");
            }
            if (tam == 0) tam = strlen(palavbras[i]);
            else if (tam < strlen(palavbras[i])) tam = strlen(palavbras[i]);
        }
        if (espaco) printf("\n");
        espaco = true;
        for (int i = 0; i < n; i++) {
            printf("%*s\n", tam, palavbras[i]);
        }
        scanf("%d", &n);
        tam = 0;
    }
    return 0;
}
