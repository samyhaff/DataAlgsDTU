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

        for (auto& edge: node->neighbors) {
            Node *neighbor = edge.second;
            if (visited.find(neighbor) == visited.end() && edge.first > 0) {
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

int get_bottleneck(vector<Node *> path) {
    int capacity, bottleneck = INT_MAX;
    Node *in_node, *out_node;

    for (auto i = 0; i < path.size() - 1; i++) {
        in_node = path[i];
        out_node = path[i + 1];
        for (auto& edge: in_node->neighbors) {
            Node *tmp = edge.second;
            if (tmp == out_node) {
                capacity = edge.first;
                if (capacity < bottleneck) bottleneck = capacity;
                break;
            }
        }
    }

    return bottleneck;
}

int augment(vector<Node *> path) {
    int bottleneck = get_bottleneck(path);
    Node *in_node, *out_node;
    bool found_edge = false;

    for (auto i = 0; i < path.size() - 1; i++) {
        in_node = path[i];
        out_node = path[i + 1];
        found_edge = false;

        // forward edge
        for (auto& edge: in_node->neighbors) {
            Node *tmp = edge.second;
            if (tmp == out_node) {
                edge.first -= bottleneck;
                break;
            }
        }

        // backward_edge
        for (auto& edge: out_node->neighbors) {
            Node *tmp = edge.second;
            if (tmp == in_node) {
                found_edge = true;
                edge.first += bottleneck;
                break;
            }
        }

        if (!found_edge)
            out_node->neighbors.push_back(make_pair(bottleneck, in_node));

    }

    return bottleneck;
}

int max_flow(Node *start, Node *end) {
    vector<Node *> path;
    int max_flow = 0;

    while ((path = get_path(start, end)).size() > 0)
        max_flow += augment(path);

    return max_flow;
}
