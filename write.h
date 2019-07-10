# pragma once

#include "graph.h"
#include <fstream>
#include <string>

void uploadData(std::string& path_nodes, std::string& path_edges, Graph& G) {
    std::ofstream file_nodes, file_edges;
    // Writing a file with edges
    file_edges.open(path_edges);
    file_edges << "Source" << ',' << "Target" << std::endl;
    for (std::pair<std::string, std::string> edge : G.edges) {
        file_edges << edge.first << ',' << edge.second << std::endl;
    }
    // Writing a file with nodes
    file_nodes.open(path_nodes);
    file_nodes << "Id" << ',' << "Label" << std::endl;
    for (std::pair<std::string, Node> p : G.nodes) {
        file_nodes << p.first << ',' << p.second.label << std::endl;
    }
    file_edges.close();
    file_nodes.close();
}