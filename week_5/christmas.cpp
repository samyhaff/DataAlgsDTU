#include <bits/stdc++.h>
#include "ford_fulkerson.h"

using namespace std;

#define MAX_TREES_ROW 2
#define MAX_TREES_COL 1
#define MAX_TABLES_SQUARE 1

int main() {
    int n, m;

    cin >> n >> m;

    __uint16_t **graph = new __uint16_t*[n + m + 2];
    __uint16_t **res_graph = new __uint16_t*[n + m +2];
    for (int i = 0; i < n + m + 2; i++) {
        graph[i] = new __uint16_t[n + m + 2];
        res_graph[i] = new __uint16_t[n + m + 2];
    }

    /*
    0: start
    1-n: rows
    n+1:n+m: cols
    n+m++1: end
    */

    for (int i = 1; i <= n; i++)
        graph[0][i] = MAX_TREES_ROW;
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= n + m; j++)
            graph[i][j] = MAX_TABLES_SQUARE;
    for (int i = n + 1; i <= n + m; i++)
        graph[i][n + m + 1] = MAX_TREES_COL;

    int n_trees, col;
    for (int i = 0; i < n; i++) {
        cin >> n_trees;
        for (int j = 0; j < n_trees; j++) {
            cin >> col;
            graph[i + 1][n + col + 1] = 0;
        }
    }

    // for (int i = 0; i < n + m + 2; i++) {
    //     for (int j = 0; j < n + m + 2; j++)
    //         cout << graph[i][j] << " ";
    //     cout << endl;
    // }

    for (int i = 0; i < n + m + 2; i++)
        for (int j = 0; j < n + m + 2; j++)
             res_graph[i][j] = graph[i][j];

    cout << max_flow(res_graph, graph, n + m + 2, 0, n + m + 1);

    return 0;
}
