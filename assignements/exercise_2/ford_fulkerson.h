#pragma once

#include "graph.h"
#include <vector>

std::vector<Node *> get_path(Node *start, Node *end);
int get_bottleneck(std::vector<Node *> path);
