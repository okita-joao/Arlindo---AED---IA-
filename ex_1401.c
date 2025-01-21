#include <stdio.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int next_permutation(char *str, int len) {
    int i = len - 1;
    while (i > 0 && str[i - 1] >= str[i]) {
        i--;
    }
    
    if (i <= 0) {
        return 0; // Nenhuma permutação possível
    }

    int j = len - 1;
    while (str[j] <= str[i - 1]) {
        j--;
    }

    swap(&str[i - 1], &str[j]);
    
    // Reverte a substring após a posição i-1
    j = len - 1;
    while (i < j) {
        swap(&str[i], &str[j]);
        i++;
        j--;
    }
    
    return 1; // Permutação gerada
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();
    
    char perm[20];
    
    while (n--) {
        scanf(" %[^\n]", perm);
        int tam = strlen(perm);
        
        // Ordena a string
        for (int i = 0; i < tam - 1; i++) {
            for (int j = i + 1; j < tam; j++) {
                if (perm[i] > perm[j]) {
                    swap(&perm[i], &perm[j]);
                }
            }
        }
        
        do {
            printf("%s\n", perm);
        } while (next_permutation(perm, tam));
        
        printf("\n");
    }

    return 0;
}
