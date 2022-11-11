#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

Node *get_farthest_node(Node node, vector<Node> nodes) {
    int distance, max_distance = 0;
    Node *res = NULL;

    for (auto& candidate: nodes) {
        distance = (node.zone->x - candidate.zone->x)  * (node.zone->x - candidate.zone->x)
            + (node.zone->y - candidate.zone -> y) * (node.zone->y - candidate.zone -> y);
        if (distance > max_distance) {
            max_distance = distance;
            res = &candidate;
        }
    }

    return res;
}

void create_graph(vector<Node> &nodes) {
    int n = nodes.size();
    Node *end = &nodes[n - 1];
    int capacity;

    for (auto& node: nodes) {
        // 01
        if ((capacity = node.zone->restrictions[0]) > 0) {
            Node *new_node = new Node;
            new_node->zone = NULL;
            node.neighbors.push_back(make_pair(capacity, new_node));

            for (auto& candidate: nodes) {
                if (&candidate != &node &&
                    (candidate.zone->x == node.zone->x || candidate.zone->y == node.zone->y)) {
                    new_node->neighbors.push_back(make_pair(INT_MAX, &candidate));
                }
            }
        }

        // 02
        if ((capacity = node.zone->restrictions[1]) > 0) {
            Node *new_node = new Node;
            new_node->zone = NULL;
            node.neighbors.push_back(make_pair(capacity, new_node));
            Node *farthest_node = get_farthest_node(node, nodes);
            if (farthest_node != NULL)
                new_node->neighbors.push_back(make_pair(INT_MAX, farthest_node));
        }

        // 03
        // TODO

        // 04
        if ((capacity = node.zone->restrictions[3]) > 0) {
            Node *new_node = new Node;
            new_node->zone = NULL;
            new_node->neighbors.push_back(make_pair(INT_MAX, end));
            node.neighbors.push_back(make_pair(capacity, new_node));
        }
    }
}
