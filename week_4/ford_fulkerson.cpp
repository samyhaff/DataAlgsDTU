#include <bits/stdc++.h>

using namespace std;

void print_graph(int **graph, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
}

vector<int> get_path(int **graph, int n, int start, int end) {
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

int get_bottleneck(int **graph, vector<int> path) {
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

void augment(int **graph, vector<int> path) {
    int in_node, out_node;
    int bottleneck = get_bottleneck(graph, path);

    for (int i = 0; i < path.size() - 1; i++) {
        in_node = path[i];
        out_node = path[i + 1];
        graph[in_node][out_node] -= bottleneck;
        graph[out_node][in_node] += bottleneck;
    }
}

// int ford_fulkerson(int **graph, int n, int start, int end) {
//
// }

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

    // test
    print_graph(graph, n);
    vector<int> path = get_path(graph, n, 0, 1);
    augment(graph, path); cout << endl;
    print_graph(graph, n);

    return 0;
}
