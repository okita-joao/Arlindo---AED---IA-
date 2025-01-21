#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 1000

typedef struct {
    char item[50];
    float valor;
} Feira;

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        int m, p;
        Feira feira[MAX_ITEMS];
        int count = 0;
        float final = 0.0;

        scanf("%d", &m);
        while (m--) {
            char item[50];
            float valor;
            scanf("%s %f", item, &valor);
            strcpy(feira[count].item, item);
            feira[count].valor = valor;
            count++;
        }

        scanf("%d", &p);
        while (p--) {
            char item[50];
            int qt;
            scanf("%s %d", item, &qt);
            for (int i = 0; i < count; i++) {
                if (strcmp(feira[i].item, item) == 0) {
                    final += feira[i].valor * qt;
                    break;
                }
            }
        }

        printf("R$ %.2f\n", final);
    }

    return 0;
}
