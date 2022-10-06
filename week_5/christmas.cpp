#include <bits/stdc++.h>

using namespace std;

#define MAX_TREES_ROW 2
#define MAX_TREES_COL 1

vector<int> get_path(__uint16_t **graph, int n, int start, int end) {
    vector<int> path;
    bool *visited = new bool[n];
    int *parent = new int[n];
    stack<int> stack;
    int v;
    bool found = false;

    stack.push(start);
    for (int i = 0; i < n; i++) visited[i] = false;
    visited[start] = true;

    while (!stack.empty()) {
        v = stack.top(); stack.pop();
        if (v == end) {
            found = true;
            break;
        }

        for (int i = 0; i < n; i++) {
            if (graph[v][i] > 0 and !visited[i]) {
                stack.push(i);
                visited[i] = true;
                parent[i] = v;
            }
        }
    }

    if (found) {
        v = end;
        path.push_back(v);
        while (v != start) {
            v = parent[v];
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
    }

    delete[] visited;
    delete[] parent;
    return path;
}

int get_bottleneck(__uint16_t **graph, vector<int> path) {
    int in_node, out_node, capacity;
    int bottleneck = graph[path[0]][path[1]];

    for (int i = 1; i < path.size() - 1; i++) {
        in_node = path[i];
        out_node = path[i + 1];
        capacity = graph[in_node][out_node];
        if (capacity < bottleneck) bottleneck = capacity;
    }

    return bottleneck;
}

void augment(__uint16_t **graph, vector<int> path) {
    int in_node, out_node;
    int bottleneck = get_bottleneck(graph, path);

    for (int i = 0; i < path.size() - 1; i++) {
        in_node = path[i];
        out_node = path[i + 1];
        graph[in_node][out_node] -= bottleneck;
        graph[out_node][in_node] += bottleneck;
    }
}

int max_flow(__uint16_t **res_graph, __uint16_t **graph, int n, int start, int end) {
    vector<int> path;
    int max_flow = 0;

    while ((path = get_path(res_graph, n, start, end)).size() > 0)
        augment(res_graph, path);

    for (int i = 0; i < n; i++)
        if (graph[i][start] == 0) max_flow += res_graph[i][start];

    return max_flow;
}

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
            graph[i][j] = 1; // each row can only be matched once with each column
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
