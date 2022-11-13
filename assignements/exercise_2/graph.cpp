#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

Node *create_node(Node *node, int capacity) {
    Node *new_node = new Node;
    new_node->zone = NULL;
    node->neighbors.push_back(make_pair(capacity, new_node));
    return new_node;
}

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
            Node *new_node = create_node(&node, capacity);

            for (auto& candidate: nodes) {
                if (&candidate != &node &&
                    (candidate.zone->x == node.zone->x || candidate.zone->y == node.zone->y)) {
                    new_node->neighbors.push_back(make_pair(INT_MAX, &candidate));
                }
            }
        }

        // 02
        if ((capacity = node.zone->restrictions[1]) > 0) {
            Node *new_node = create_node(&node, capacity);

            Node *farthest_node = get_farthest_node(node, nodes);
            if (farthest_node != NULL)
                new_node->neighbors.push_back(make_pair(INT_MAX, farthest_node));
        }

        // 03
        if ((capacity = node.zone->restrictions[2]) > 0) {
            Node *new_node = create_node(&node, capacity);

            for (auto& candidate: nodes) {
                int count = 0;
                for (auto& n: nodes) {
                    int det = node.zone->x * (n.zone->y * candidate.zone->y)
                        + n.zone->x * (candidate.zone->y - node.zone->y)
                        + candidate.zone->x * (node.zone->y - n.zone->y);
                    int scalar_1 = (candidate.zone->x - node.zone->x) * (n.zone->x - node.zone->x)
                        + (candidate.zone->y - node.zone->y) * (n.zone->y - node.zone->y);
                    int scalar_2 = (candidate.zone->x - node.zone->x) * (candidate.zone->x - node.zone->x)
                        + (candidate.zone->y - node.zone->y) * (candidate.zone->y - node.zone->y);

                    if (det == 0 && (0 < scalar_1) && (scalar_1 < scalar_2))
                        count++;
                }

                if (count >= 2)
                    new_node->neighbors.push_back(make_pair(INT_MAX, &candidate));
            }
        }

        // 04
        if ((capacity = node.zone->restrictions[3]) > 0) {
            Node *new_node = create_node(&node, capacity);

            new_node->neighbors.push_back(make_pair(INT_MAX, end));
        }
    }
}
