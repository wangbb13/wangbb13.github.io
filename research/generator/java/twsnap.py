# -*- coding: utf-8 -*-
# python version: python 2.7
# 
# several methods: 
# TrillionG: graph/part-00000 ..., TSV; ID from 0; omit 0; directed 
# FastKronecker: specified, TCV; ID from 0; omit 4; directed 
# RMAT: specified, TSV; ID from 0; omit 0; directed 
# ROLL: specified, TSV; ID from 0; omit 0; undirected 
# gMark: roles, TSV, from type to; ID from 0; omit 0; directed 
# LFR: network.data, TSV; ID from 1; omit 0; directed 
# SNG: data/follow/data.adj, ADJ; ID from 0; omit 0; directed
# 
# function: diameter, average short path, cluster coefficient 
import os
import sys
import snap
import traceback


def command():
    """
    run generator
    """
    pass


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
                    graph.AddEdge(a, b)
                except Exception as e:
                    try:
                        graph.AddNode(a)
                    except Exception as e:
                        pass
                    try:
                        graph.AddNode(b)
                    except Exception as e:
                        pass
                    try:
                        graph.AddEdge(a, b)
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
                        graph.AddEdge(src, tgt)
                    except Exception as e:
                        if flag:
                            try:
                                graph.AddNode(src)
                            except Exception as e:
                                pass
                            flag = False
                        try:
                            graph.AddNode(tgt)
                        except Exception as e:
                            pass
                        try:
                            graph.AddEdge(src, tgt)
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
        graph = snap.TNGraph.New()
    else:
        graph = snap.TUNGraph.New()
    for _ in range(id_from, nodes + id_from):
        graph.AddNode(_)
    if not os.path.exists(filename):
        print filename, 'does not exist'
    if os.path.isdir(filename): # TrillionG
        for _, _, files in os.walk(filename):
            for file in files:
                if '.' not in file and file != '_SUCCESS':
                    load_one_file(os.path.join(filename, file), graph, omit, id_from, tsv)
    elif os.path.isfile(filename):
        load_one_file(filename, graph, omit, id_from, tsv)
    return graph


def evaluate(snap_graph):
    # diameter, avg path length
    result = snap.GetBfsEffDiamAll(snap_graph, 10, True)
    print 'diamter =', result[2]
    print 'avgSPL  =', result[3]
    # cluster coefficient
    cc = snap.GetClustCf(snap_graph, -1)
    print 'ClustCf =', cc


def main():
    """
    parameters:
    1: filename
    2: nodes
    3: directed or not
    4: omit first n lines
    5: id from 0 or 1
    6: tsv or adj
    """
    if len(sys.argv) != 7:
        print 'Usage: python2', os.path.basename(__file__), 'data_file, nodes, directed, omit, id_from, tsv_or_adj'
        exit(0)
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
    print ""
    print "=" * 30
    graph = load(filename, nodes, d_ud, omit, id_from, tsv)
    evaluate(graph)
    print "=" * 30
    print ""


if __name__ == '__main__':
    main()
