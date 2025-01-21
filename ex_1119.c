#include <stdio.h>

int main() {
    int N, K, M, a, b, c, i, e, f;
    int v[1000];

    while (scanf("%d %d %d", &N, &K, &M) && N) {
        e = 0;
        f = N - 1;

        // Inicializando o vetor v
        for (i = 0; i < N; i++) {
            v[i] = i + 1;
        }

        c = 0;

        // Processo de eliminação
        while (c < N) {
            // Encontrar o 'a' no sentido horário
            i = K;
            while (i > 0) {
                if (v[e] > 0) i--;
                if (i == 0) a = e;
                e = (e + 1) % N;
            }

            // Encontrar o 'b' no sentido anti-horário
            i = M;
            while (i > 0) {
                if (v[f] > 0) i--;
                if (i == 0) b = f;
                f = (f + N - 1) % N;
            }

            // Imprimir os resultados
            if (c > 0)
                printf(",");

            if (a != b) {
                printf("%3d%3d", v[a], v[b]);
                c += 2;
            } else {
                printf("%3d", v[a]);
                c++;
            }

            v[a] = v[b] = 0;  // Eliminando as pessoas
        }

        printf("\n");
    }

    return 0;
}
