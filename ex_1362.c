#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NODES 500

int bfs(int s, int t, int parent[], int rg[NODES][NODES]) {
    int vis[NODES];
    memset(vis, 0, sizeof(vis));
    int queue[NODES], front = 0, rear = 0;
    queue[rear++] = s;
    vis[s] = 1;
    parent[s] = -1;

    while (front < rear) {
        int x = queue[front++];
        for (int i = 0; i < NODES; ++i) {
            if (!vis[i] && rg[x][i] > 0) {
                queue[rear++] = i;
                parent[i] = x;
                vis[i] = 1;
            }
        }
    }
    return vis[t];
}

int fordFulkerson(int g[NODES][NODES], int s, int t) {
    int rg[NODES][NODES];
    memcpy(rg, g, sizeof(rg));
    int parent[NODES];
    int max_flow = 0;

    while (bfs(s, t, parent, rg)) {
        int path_flow = 0x3f3f3f3f;
        for (int i = t; i != s; i = parent[i]) {
            int x = parent[i];
            path_flow = fmin(path_flow, rg[x][i]);
        }
        for (int i = t; i != s; i = parent[i]) {
            int x = parent[i];
            rg[x][i] -= path_flow;
            rg[i][x] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int getSizeIndex(char *size) {
    if (strcmp(size, "XXL") == 0) return 1;
    if (strcmp(size, "XL") == 0) return 2;
    if (strcmp(size, "L") == 0) return 3;
    if (strcmp(size, "M") == 0) return 4;
    if (strcmp(size, "S") == 0) return 5;
    if (strcmp(size, "XS") == 0) return 6;
    return -1;
}

int main() {
    int graph[NODES][NODES];
    int test_cases, N, M, soc;
    char a[4], b[4];

    scanf("%d", &test_cases);
    while (test_cases--) {
        scanf("%d %d", &N, &M);
        memset(graph, 0, sizeof(graph));
        soc = N / 6;

        for (int i = 1; i <= 6; ++i) {
            graph[0][i] = soc;
        }

        for (int i = 1; i <= M; ++i) {
            scanf("%s %s", a, b);
            int idx_a = getSizeIndex(a);
            int idx_b = getSizeIndex(b);
            int shirt_node = 6 + i;

            graph[idx_a][shirt_node] = 1;
            graph[idx_b][shirt_node] = 1;
            graph[shirt_node][M + 7] = 1;
        }

        int ans = fordFulkerson(graph, 0, M + 7);
        printf(ans == M ? "YES\n" : "NO\n");
    }
    return 0;
}
