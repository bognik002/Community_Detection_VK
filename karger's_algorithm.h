#pragma once

#include "graph.h"
#include <vector>
#include <string>
#include <ctime>


int rand_int(const int first, const int last) {
    std::time_t t = std::time(nullptr);
    unsigned int seed;
    seed = static_cast<unsigned int>(t);
    srand(seed);
    return rand() % (last - first) + first;
}


void algorithmKarger(Graph& G, int count) {
    int n = G.edges.size();
    while (n > count) {
        std::pair<std::string, std::string> edge = G.edges[rand_int(0, n)];
        G.contract(edge);
        n = G.edges.size();
    }
}