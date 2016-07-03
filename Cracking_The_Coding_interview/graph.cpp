/*
    Graph is a structure which is non-linear and unlike a ttree has no order.
    ie there is no parent or child, nodes are connected in random manner
    they can even be loops in the structure
    A graph G is an ordered pair of a set V of vertices and a set E of edges.
            G = (V,E)
    Notation for an ordered pair:-
        (a,b) != (b,a) if a!=b
    Notation for unordered pair:-
        {a,b} == {b,a}
    Edge here is a link -> can be directed (a,b) or undirected {a,b)
    Vertices are nodes.
    A Directed graph i.e all edges are directed is called a Digraph.
        DiGraph can have bidirectional edges too but it has atleast onne unidirectional
        graph.
    Eg:-
        Friend relation in facebook -> undirected graph as if A is a friend of B
        then B is also a friend of A.
        Webcrawler -> Directional graph

    Unweighted graph -> All edges have a weight = 1 unit
    Weighted Graph -> Heuristics
*/
/*
    Properties of a graph:-
        a. Self loop -> eg. Home page has a home button, clicking on which takes you to
        the same page.
        b. Multi edge -> More than one DIRECT links between 2 nodes
                            can be directed or undirected.
                        Links need to be in the same direction.
        A Simple graph is one with no Multi Edge or a Self loop.
        For a Graph with N Vertices, max no of edges = N * N-1 in a Simple Directed graph
        For Undirected graph = N * (N-1)/2



