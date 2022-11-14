#include <bits/stdc++.h>
#include "graph.h"
#include "ford_fulkerson.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<Node> nodes(n);

    for (int i = 0; i <n; i++) {
        Zone *z = new Zone;
        cin >> z->x >> z->y >> z->restrictions[0] >> z->restrictions[1]
            >> z->restrictions[2] >> z->restrictions[3];
        nodes[i].zone = z;
    }

    create_graph(nodes);
    for (auto node: nodes)
        cout << node.neighbors.size() << " ";
    cout << endl;

    vector<Node *> path = get_path(&nodes[0], &nodes[n - 1]);
    for (Node *node: path)
        if (node->zone)
            cout << node->zone->x << " " << node->zone->y << endl;

    return 0;
}
