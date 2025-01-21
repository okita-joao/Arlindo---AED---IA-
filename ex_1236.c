#include <stdio.h>
#include <string.h>
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void compress(char toCompress, int times, char *result) {
    if (times > 2) {
        char compressChar = (toCompress == ' ') ? '$' : '#';

        while (times > 0) {
            int chunk = MIN(255, times);
            strncat(result, &compressChar, 1);
            char chunkChar = (char) chunk;
            strncat(result, &chunkChar, 1);
            times -= 255;
        }
    } else {
        for (int i = 0; i < times; i++) {
            strncat(result, &toCompress, 1);
        }
    }
}

int main() {
    int n;
    char line[1001]; // Array para armazenar a linha de entrada

    // Leitura do número de casos de teste
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        // Leitura da linha
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0'; // Remove a quebra de linha

        char out[10000] = ""; // String para armazenar o resultado
        int lastStart = -1;

        for (int j = 0; j < strlen(line); ++j) {
            if (lastStart != -1 && line[j] != line[j - 1]) {
                compress(line[j - 1], j - lastStart, out);
                lastStart = -1;
            }

            if (line[j] == ' ' || line[j] == '0') {
                lastStart = (lastStart == -1) ? j : lastStart;
            } else {
                strncat(out, &line[j], 1);
            }
        }

        if (lastStart != -1) {
            compress(line[lastStart], strlen(line) - lastStart, out);
        }

        // Imprime a linha comprimida
        printf("%s\n", out);
    }

    return 0;
}
