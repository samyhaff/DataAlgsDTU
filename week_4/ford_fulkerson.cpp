#include <bits/stdc++.h>

using namespace std;

bool get_path(int **graph, int n, int start, int end) {
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

    delete[] visited;
    delete[] parent;
    return found;
}

int main() {
    int n, m;
    int in_node, out_node, capacity;

    cin >> n >> m;
    int **graph = new int*[n];
    for (int i = 0; i < n; i++)
        graph[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    for (int i = 0; i < m; i++) {
        cin >> in_node >> out_node >> capacity;
        graph[in_node][out_node] = capacity;
    }

    cout << get_path(graph, n, 0, 1);

    return 0;
}
