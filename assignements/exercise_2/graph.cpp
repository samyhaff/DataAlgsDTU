#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

void create_graph(vector<Node> &nodes) {
    int n = nodes.size();
    Node *end = &nodes[n - 1];
    int capacity;

    for (auto& node: nodes) {
        // 04
        if ((capacity = node.zone->restrictions[3]) > 0) {
            Node *new_node = new Node;
            new_node->zone = NULL;
            new_node->neighbors.push_back(make_pair(INT_MAX, end));
            node.neighbors.push_back(make_pair(capacity, new_node));
        }
    }
}
