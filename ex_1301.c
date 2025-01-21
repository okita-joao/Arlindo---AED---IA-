#include <stdio.h>
#include <string.h>

#define AVN 400003
#define VTN 100002

int st[AVN];
int v[VTN];

int valor(int a) {
    return (a > 0 ? 1 : (a < 0 ? -1 : 0));
}

void init(int index, int a, int b) {
    if (a == b)
        st[index] = valor(v[a - 1]);
    else {
        int m = (b + a) / 2;
        init(2 * index, a, m);
        init(2 * index + 1, m + 1, b);
        st[index] = st[index * 2] * st[index * 2 + 1];
    }
}

void update(int index, int a, int b, int i, int x) {
    if (i > b || i < a) return;
    if (a == b && b == i) {
        st[index] = valor(x);
        return;
    }
    int m = (a + b) / 2;
    update(2 * index, a, m, i, x);
    update(2 * index + 1, m + 1, b, i, x);
    st[index] = st[index * 2] * st[index * 2 + 1];
}

int query(int index, int a, int b, int i, int j) {
    if (i > b || j < a) return 1;
    if (a >= i && b <= j) return st[index];
    int m = (a + b) / 2;
    int x0 = query(index * 2, a, m, i, j);
    int x1 = query(index * 2 + 1, m + 1, b, i, j);
    return x1 * x0;
}

int main() {
    char c;
    int a, b, n, q;

    while (scanf("%d %d", &n, &q) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);

        init(1, 1, n);
        for (int i = 0; i < q; i++) {
            scanf(" %c %d %d", &c, &a, &b);
            if (c == 'P') {
                int answer = query(1, 1, n, a, b);
                printf("%c", (answer == 1 ? '+' : (answer == 0 ? '0' : '-')));
            } else if (c == 'C') {
                update(1, 1, n, a, b);
            }
        }
        printf("\n");
    }
    return 0;
}
