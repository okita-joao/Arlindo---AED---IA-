#include <stdio.h>
#include <string.h>

int main() {
    int n, i, j, zero, cont;
    long long int num;
    char number[101];

    while (scanf("%d", &n) == 1) {
        scanf("%s", number);

        if (n == 0 && number[0] == '0') break;

        char changed[101];
        i = 0;
        j = 0;
        zero = 0;
        num = 0;
        cont = 0;

        while (1) {
            if (number[i] == '\0') {
                break;
            } else if (number[i] == n + 48) {
                i++;
            } else {
                changed[j] = number[i];
                if (j == zero) cont++;
                if (number[i] == '0') zero++;
                i++;
                j++;
            }
        }
        changed[j] = '\0';

        // Convert the changed string to a long long integer
        num = 0;
        for (int k = 0; changed[k] != '\0'; k++) {
            num = num * 10 + (changed[k] - '0');
        }

        if (j == 0) {
            printf("0\n");
        } else if (j == zero) {
            printf("%lld\n", num);
        } else if (cont > 0) {
            for (int k = cont - 1; changed[k] != '\0'; k++) {
                printf("%d", changed[k] - '0');
            }
            printf("\n");
        } else {
            printf("%s\n", changed);
        }
    }

    return 0;
}
