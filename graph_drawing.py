import networkx as nx
import csv
import codecs
from karger_algorithm import karger_algorithm
from networkx.algorithms import community

G = nx.Graph()
info = dict()
with codecs.open("data/small_nodes.csv", 'r', 'utf-8') as file:
    csv_reader = csv.reader(file)
    nodes = []
    for row in csv_reader:
        nodes.append(row[0])
        info[row[0]] = row[1]

with codecs.open("data/small_edges.csv", 'r', 'utf-8') as file:
    csv_reader = csv.reader(file)
    edges = []
    for row in csv_reader:
        edges.append([row[0], row[1]])

G.add_nodes_from(nodes[1:])
G.add_edges_from(edges[1:])
G.to_undirected_class()

# Draw KClique
cliques = list(community.k_clique_communities(G, 5))
with codecs.open("data/friends_Kclique_edges.csv", 'w', "utf-8") as file_edges,\
    codecs.open("data/friends_Kclique_nodes.csv", 'w', "utf-8") as file_nodes:
    file_nodes_writer = csv.writer(file_nodes)
    file_nodes_writer.writerow(['Id', 'Label'])
    file_edges_writer = csv.writer(file_edges)
    file_edges_writer.writerow(['Source', 'Target'])
    list_edges = []
    for clique in cliques:
        for c1 in clique:
            file_nodes_writer.writerow([c1, info[c1]])
            for c2 in clique:
                if c1 != c2:
                    if [c1, c2] not in list_edges:
                        list_edges.append([c1, c2])
    for edge in list_edges:
        file_edges_writer.writerow(edge)


# Draw Karger's
with codecs.open("data/friends_Karger_edges.csv", 'w', "utf-8") as file_edges,\
    codecs.open("data/friends_Karger_nodes.csv", 'w', "utf-8") as file_nodes:
    csv_writer_edges = csv.writer(file_edges)
    csv_writer_edges.writerow(['Source', 'Target'])
    csv_writer_nodes = csv.writer(file_nodes)
    csv_writer_nodes.writerow(['Id', 'Label'])
    scc = nx.connected_component_subgraphs(G)
    i = 0
    for g in scc:
        for i in range(50):
            i += 1
            print(i)
            min_cut = karger_algorithm(g, 2)
            for edge in min_cut.edges():
                csv_writer_edges.writerow(list(edge))
            for node in min_cut.nodes():
                csv_writer_nodes.writerow([node, info[node]])