#pragma once

#include <vector>
#include <utility>

#define N_OBSTACLES 4

struct Zone {
    unsigned int x, y;
    unsigned int restrictions[N_OBSTACLES];
};

struct Node {
    Zone *zone;
    std::vector<std::pair<unsigned int, Node*>> neighbors;
};

void create_graph(std::vector<Node>&);
