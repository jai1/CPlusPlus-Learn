/*
    Trees are used for hierarchical structures.
    Each node has data and reference to it's Children.
    The links are not bidirectional i.e we can go from parent
    to child but not the other way.
    Tree is a recursive structure.

    Nomenclature:-
    Root -> Topmost node.
    Parent
    Children
    Sibling -> Nodes having same parent
    Leaf Node -> Has no child
    Grand parent -> Parent to parent
    Cousins -> Nodes having same Parent but having same
                Grand parent.
    Edges-> all nodes except the root and leaf nodes
    Ancestor
    Descendants

    Calculation:-
    For a tree with N Nodes
    - N-1 Edges
    - Height of a Node is the max no of edges between the  node
      and any one of it's Descendant Leaf node.
      Height of an empty tree is -1.
      Height of a tree with only root node is 0 (1 node)
    - Height of a Tree = Height of Root Node
    - Depth of a Node is the number of Edges between the Node
      and the Root Node.

    Application of Trees:-
    a. Store hierarchical data
        - File System
        -
    b. Organizing data for quick search, insertion and deletion
        - Binary Search Tree
        - Trie for storing dictionary and quick spell checks
    c. Network routing algorithms
*/

