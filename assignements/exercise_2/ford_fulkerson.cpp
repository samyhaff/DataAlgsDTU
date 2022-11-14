#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

vector<Node *> get_path(Node *start, Node *end) {
    vector<Node *> path;
    unordered_set<Node *> visited;
    stack<Node *> stack;
    bool found = false;
    Node *node;
    unordered_map<Node *, Node *> parent;

    stack.push(start);
    visited.insert(start);

    while (!stack.empty()) {
        node = stack.top(); stack.pop();
        if (node == end) {
            found = true;
            break;
        }

        for (auto edge: node->neighbors) {
            Node *neighbor = edge.second;
            if (visited.find(neighbor) == visited.end()) {
                stack.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = node;
            }
        }
    }

    if (found) {
        node = end;
        path.push_back(node);
        while (node != start) {
            node = parent[node];
            path.push_back(node);
        }
        reverse(path.begin(), path.end());
    }

    return path;
}
