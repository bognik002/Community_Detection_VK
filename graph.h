#pragma once

#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>


std::string concatinate(std::string& s1, std::string& s2) {
    std::string res;
    std::string sep = " | ";
    res = s1 + sep + s2;
    return res;
}

bool check_edge(std::set<std::pair<std::string, std::string>>& edges, std::pair<std::string, std::string>& edge) {
    std::pair<std::string, std::string> edge_reverse;
    edge_reverse.first = edge.second;
    edge_reverse.second = edge.first;
    return ((edges.find(edge) != edges.end()) || (edges.find(edge_reverse) != edges.end()));
}

struct Node {
    std::string id;
    std::string label;
};


class Graph {
public:
    std::map<std::string, Node> nodes;
    std::vector<std::pair<std::string, std::string>> edges;

    Graph() {
        edges.resize(0);
    }

    void addNode(Node n) {
        nodes[n.id] = n;
    }

    void addEdge(std::string n1, std::string n2) {
        std::pair<std::string, std::string> p;
        p.first = n1;
        p.second = n2;
        edges.push_back(p);
    }

    void deleteNode(Node n) {
        nodes.erase(n.id);
    }

    void deleteEdge(std::pair<std::string, std::string>& edge) {
        edges.erase(std::find(edges.begin(), edges.end(), edge));
    }

    void delete_loops() {
        std::vector<std::pair<std::string, std::string>> result;
        std::set<std::pair<std::string, std::string>> set_edges;
        for (std::pair<std::string, std::string> edge : edges) {
            std::pair<std::string, std::string> reverse;
            reverse.first = edge.second;
            reverse.second = edge.first;
            if ((set_edges.find(reverse) == set_edges.end()) && (set_edges.find(edge) == set_edges.end())) {
                result.push_back(edge);
                set_edges.insert(edge);
            }
        }
        edges = result;
    }

    void contract(std::pair<std::string, std::string>& edge_to_delete) {
        Node node;
        node.id = concatinate(edge_to_delete.first, edge_to_delete.second);
        node.label = concatinate(nodes[edge_to_delete.first].label, nodes[edge_to_delete.second].label);
        deleteEdge(edge_to_delete);
        for (std::pair<std::string, std::string>& edge : edges) {
            if ((edge.first == edge_to_delete.first) || (edge.first == edge_to_delete.second)) {
                edge.first = node.id;
            } else if ((edge.second == edge_to_delete.first) || (edge.second == edge_to_delete.second)) {
                edge.second = node.id;
            }
        }
        delete_loops();
        deleteNode(nodes[edge_to_delete.first]);
        deleteNode(nodes[edge_to_delete.second]);
        addNode(node);
    }

    std::vector<std::string> find_way(std::set<std::string>& visited, std::string& pos) {
        std::vector<std::string> result;
        for (std::pair<std::string, std::string>& edge : edges) {
            if (edge.first == pos) {
                if (visited.find((visited.begin(), visited.end(), edge.second)) == visited.end()) {
                    result.push_back(edge.second);
                }
            } else if (edge.second == pos) {
                if (visited.find((visited.begin(), visited.end(), edge.first)) == visited.end()) {
                    result.push_back(edge.first);
                }
            }
        }
        return result;
    }

    void Dfs(std::set<std::string>& visited, std::string pos) {
        if (pos.empty()) {
            return;
        }
        std::vector<std::string> destination = find_way(visited, pos);
        if (!(destination.empty())) {
            for (std::string dest : destination) {
                visited.insert(dest);
                Dfs(visited, dest);
                visited.erase(dest);
            }
        }
    }

    std::vector<Graph> getSCC() {
        std::vector<Graph> result;
        std::set<std::string> covered;
        std::set<std::string> visited;
        for (std::pair<std::string, Node> node : nodes) {
            std::string pos = node.first;
            Graph graph;
            if (std::find(covered.begin(), covered.end(), pos) == covered.end()) {
                visited.clear();
                visited.insert(pos);
                std::set<std::pair<std::string, std::string>> scc_edges;
                Dfs(visited, pos);
                for (std::string s : visited) {
                    covered.insert(s);
                    Node vertex = nodes[s];
                    graph.addNode(vertex);
                    for (std::pair<std::string, std::string>& edge : edges) {
                        if ((edge.first == vertex.id) || (edge.second == vertex.id)) {
                            scc_edges.insert(edge);
                        }
                    }
                }
                for (std::pair<std::string, std::string> edge : scc_edges) {
                    graph.addEdge(edge.first, edge.second);
                }
                result.push_back(graph);
            }
        }
        return result;
    }
};