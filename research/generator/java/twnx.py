# -*- coding: utf-8 -*-
# python 3
# networkx 2.1
# 
# several methods: 
# TrillionG: graph/part-00000 ..., TSV; ID from 0; omit 0; directed 
# FastKronecker: specified, TCV; ID from 0; omit 4; directed 
# RMAT: specified, TSV; ID from 0; omit 0; directed 
# ROLL: specified, TSV; ID from 0; omit 0; undirected 
# gMark: roles, TSV, from type to; ID from 0; omit 0; directed 
# LFR: network.data, TSV; ID from 1; omit 0; directed 
# SNG: data/follow/data.adj, ADJ; ID from 0; omit 0; directed
import os
import sys
import networkx as nx 
from datetime import datetime


def usage():
    if len(sys.argv) != 7:
        print('Usage: python3 %s filename, nodes, directed, omit, id_from, tsv_or_adj' % (os.path.basename(__file__)))
        exit(0)


def load_one_file(filename, graph, omit, id_from, tsv):
    """
    load one file
    parameters:
    filename: literaly
    graph: snap.Graph
    omit: omit first n lines
    tsv: True -> tsv, False -> adj
    id_from: start node id
    """
    first_n = 0
    if tsv:
        with open(filename, 'r') as fin:
            for line in fin:
                if first_n < omit:
                    first_n += 1
                    continue
                line = line.strip().split()
                if len(line) != 2:
                    continue
                a, b = int(line[0]), int(line[1])
                try:
                    graph.add_edge(a, b)
                except Exception as e:
                    try:
                        graph.add_node(a)
                    except Exception as e:
                        pass
                    try:
                        graph.add_node(b)
                    except Exception as e:
                        pass
                    try:
                        graph.add_edge(a, b)
                    except Exception as e:
                        pass
    else:
        with open(filename, 'r') as fin:
            for line in fin:
                if first_n < omit:
                    first_n += 1
                    continue
                line = [int(_) for _ in line.strip().split()]
                if len(line) < 2:
                    continue
                src = line[0]
                flag = True
                for tgt in line[1:]:
                    try:
                        graph.add_edge(src, tgt)
                    except Exception as e:
                        if flag:
                            try:
                                graph.add_node(src)
                            except Exception as e:
                                pass
                            flag = False
                        try:
                            graph.add_node(tgt)
                        except Exception as e:
                            pass
                        try:
                            graph.add_edge(src, tgt)
                        except Exception as e:
                            pass


def get_nodes(filename):
    ans = 0;
    stat = set()
    with open(filename, 'r') as fin:
        for line in fin:
            line = line.strip().split()
            for i in line:
                if i not in stat:
                    stat.add(i)
                    ans += 1
    return ans


def load(filename, nodes, d_ud, omit, id_from, tsv):
    """
    load graph to snap graph
    parameters: 
    filename: literaly
    d_ud: True -> directed, False -> undirected 
    omit: omit first n lines
    id_from: 0 or 1
    tsv: True -> tsv, False -> adj
    """
    if nodes == -1:
        nodes = get_nodes(filename)
    if d_ud:
        # graph = snap.TNGraph.New()
        graph = nx.DiGraph()
    else:
        # graph = snap.TUNGraph.New()
        graph = nx.Graph()
    # for _ in range(id_from, nodes + id_from):
    #     graph.AddNode(_)
    graph.add_nodes_from(range(id_from, nodes + id_from))
    if not os.path.exists(filename):
        print(filename, 'does not exist')
    if os.path.isdir(filename): # TrillionG
        for _, _, files in os.walk(filename):
            for file in files:
                if '.' not in file and file != '_SUCCESS':
                    load_one_file(os.path.join(filename, file), graph, omit, id_from, tsv)
    elif os.path.isfile(filename):
        load_one_file(filename, graph, omit, id_from, tsv)
    return graph


def evaluate(nx_graph, filename):
    # eigenvector_centrality
    eigenvector_centrality = nx.eigenvector_centrality(nx_graph)
    
    '''
    basename = os.path.basename(filename).split('.')[0]
    a = datetime.now()
    o_filename = basename + '_%d_%d_%d_.txt' % (a.hour, a.minute, a.second)
    with open(o_filename, 'w') as fout:
        for node in eigenvector_centrality:
            fout.write(str(eigenvector_centrality[node]) + '\n')
    '''

    # print(['%s %0.4f' % (node,centrality[node]) for node in centrality])
    # degree_assortativity_coefficient
    r = nx.degree_assortativity_coefficient(nx_graph)
    print('degree assortativity coefficient = %.4f' % r)


if __name__ == '__main__':
    usage()
    filename = sys.argv[1]
    nodes = int(sys.argv[2])
    if sys.argv[3] == '1':
        d_ud = True
    else:
        d_ud = False
    omit = int(sys.argv[4])
    id_from = int(sys.argv[5])
    if sys.argv[6] == '1':
        tsv = True
    else:
        tsv = False

    print(end='\n')
    print("=" * 50)
    graph = load(filename, nodes, d_ud, omit, id_from, tsv)
    evaluate(graph, filename)
    print("=" * 50)
    print(end='\n')
