#include <stdio.h>

int main() {
    int n, m;
    
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 && m == 0) {
            break;
        }

        int i = 2;
        int a = 1;
        int d = 0;

        // Se a pedra onde o presente está guardado for maior que 34, o sapo sempre consegue pegar essa pedra
        if (m > 34) {
            printf("Let me try!\n");
        } else {
            // Caso contrário, calculamos
            while (a > 0 && a <= n) {
                if (a == m) { // Se chegarmos à pedra onde o presente está
                    d++;
                    break;
                }
                // Se a pedra que estamos é menor que a pedra do presente
                else if (a < m) {
                    if (a + (2 * i - 1) <= n) {
                        a += 2 * i - 1;
                    } else {
                        a -= 2 * i - 1;
                    }
                    i++;
                }
                // Se estamos à frente da pedra do presente
                else {
                    if (a - (2 * i - 1) > 0) {
                        a -= 2 * i - 1;
                    } else {
                        a += 2 * i - 1;
                    }
                    i++;
                }
            }

            // Se encontramos a pedra com o presente, imprimimos "Let me try!", caso contrário "Don't make fun of me!"
            if (d != 0) {
                printf("Let me try!\n");
            } else {
                printf("Don't make fun of me!\n");
            }
        }
    }

    return 0;
}
