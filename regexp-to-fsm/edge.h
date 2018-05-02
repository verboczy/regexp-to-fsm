#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "node.h"
#include <list>

class Edge {
public:

    Edge();
    Edge(Node begin, Node end, char char_);

    Node get_end_node() const;
    char get_label_char() const;

private:
    Node begin_node;
    Node end_node;

    char label_char;
};

#endif
