#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXV 10010

typedef struct {
    int pai;
    int rank;
} UJoin;

UJoin pset[MAXV];
int dfs_low[MAXV], dfs_num[MAXV], dfs_parent[MAXV];
int counter, r, c, q;
int graph[MAXV][MAXV];
int graph_size[MAXV];

void Link(int x, int y) {
    if (pset[x].rank > pset[y].rank)
        pset[y].pai = x;
    else {
        pset[x].pai = y;
        if (pset[x].rank == pset[y].rank)
            pset[y].rank++;
    }
}

int findSet(int x) {
    while (pset[x].pai != x)
        x = pset[x].pai;
    return x;
}

void UnionSet(int x, int y) {
    Link(findSet(x), findSet(y));
}

int isSameSet(int x, int y) {
    return findSet(x) == findSet(y);
}

void PointBridge(int u) {
    dfs_low[u] = dfs_num[u] = counter++;
    for (int i = 0; i < graph_size[u]; i++) {
        int v = graph[u][i];
        if (!dfs_num[v]) {
            dfs_parent[v] = u;
            PointBridge(v);
            if (dfs_low[v] > dfs_num[u]) {
                if (!isSameSet(u, v))
                    UnionSet(u, v);
            }
            dfs_low[u] = fmin(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) {
            dfs_low[u] = fmin(dfs_low[u], dfs_num[v]);
        }
    }
}

int main() {
    int de, para;
    while (scanf("%d %d %d", &r, &c, &q) && r + c + q) {
        memset(dfs_parent, 0, sizeof(dfs_parent));
        memset(dfs_low, 0, sizeof(dfs_low));
        memset(dfs_num, 0, sizeof(dfs_num));
        memset(graph_size, 0, sizeof(graph_size));
        for (int i = 0; i < r; ++i) {
            pset[i].pai = i;
            pset[i].rank = 0;
        }
        for (int i = 0; i < c; ++i) {
            scanf("%d %d", &de, &para);
            graph[de - 1][graph_size[de - 1]++] = para - 1;
            graph[para - 1][graph_size[para - 1]++] = de - 1;
        }
        counter = 0;
        PointBridge(0);
        for (int i = 0; i < q; ++i) {
            scanf("%d %d", &de, &para);
            printf("%c\n", isSameSet(de - 1, para - 1) ? 'Y' : 'N');
        }
        printf("-\n");
    }
    return 0;
}
