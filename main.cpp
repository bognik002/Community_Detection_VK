#include "write.h"
#include "read.h"
#include "graph.h"
#include "karger's_algorithm.h"
#include <iostream>

void test() {
    Graph G = Graph();
    for (int i = 0; i < 5; ++i) {
        std::string id;
        std::string label;
        id.push_back((char)(48 + i));
        label.push_back((char)(97 + i));
        Node n;
        n.id = id;
        n.label = label;
        G.addNode(n);
    }
    G.addEdge("0", "1");
    G.addEdge("0", "2");
    //G.addEdge("0", "3");
    //G.addEdge("1", "3");
    //G.addEdge("2", "3");
    //G.addEdge("2", "4");
    G.addEdge("3", "4");
    std::vector<Graph> scc = G.getSCC();
    for (Graph& g : scc) {
        algorithmKarger(g, 1);
    }
}


int main() {
    std::string friends_nodes_read = "C:/Users/User/PycharmProjects/Community_Detection/data/friends_nodes.csv";
    std::string friends_edges_read = "C:/Users/User/PycharmProjects/Community_Detection/data/friends_edges.csv";
    std::string friends_nodes_write = "C:/Users/User/Documents/ClionProjects/untitled/data/friends_nodes_mod.csv";
    std::string friends_edges_write = "C:/Users/User/Documents/ClionProjects/untitled/data/friends_edges_mod.csv";
    Graph G = downloadData(friends_nodes_read, friends_edges_read);
    std::vector<Graph> scc_vector = G.getSCC();
    for (Graph& scc : scc_vector) {
        if (scc.nodes.size() > 2) {
            algorithmKarger(scc, 1);
            uploadData(friends_nodes_write, friends_edges_write, scc);
        }
    }
    return 0;
}