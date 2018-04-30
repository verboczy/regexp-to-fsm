#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "node.h"
#include <list>

class Edge {
public:

    Edge();
    Edge(Node begin, Node end, char char_);

    Edge(Edge const& other);
    Edge& operator=(Edge const& rhs);

    Edge(Edge && other);
    Edge& operator=(Edge && rhs);

    ~Edge();

    Node get_end_node() const;
    char get_label_char() const;

    Node begin_node;
    Node end_node;
private:

    char label_char;
};

#endif
