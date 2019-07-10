#pragma once

#include <fstream>
#include <vector>
#include "graph.h"

void split(std::string& line, std::string& s1, std::string& s2, char del) {
    bool flag = false;
    for (char s : line) {
        if (s == '\r') {
            return;
        }
        if (s != del) {
            if (!(flag)) {
                s1.push_back(s);
            } else {
                s2.push_back(s);
            }
        } else {
            flag = true;
        }
    }
}

Graph downloadData(std::string& path_nodes, std::string& path_edges) {
    std::ifstream file_nodes, file_edges;
    Graph G = Graph();
    // Reading a file with nodes
    file_nodes.open(path_nodes);
    std::string title_nodes;
    getline(file_nodes, title_nodes);
    Node node;
    std::string line;
    if (file_nodes.is_open()) {
        while (getline(file_nodes, line)) {
            Node node;
            split(line, node.id, node.label, ',');
            G.addNode(node);
        }
    }
    // Reading a file with edges
    file_edges.open(path_edges);
    std::string title_edges;
    getline(file_edges, title_edges);
    std::pair<std::string, std::string> edge;
    if (file_nodes.is_open()) {
        while (getline(file_edges, line)) {
            std::pair<std::string, std::string> edge;
            split(line, edge.first, edge.second, ',');
            G.addEdge(edge.first, edge.second);
        }
    }
    file_edges.close();
    file_nodes.close();
    return G;
}