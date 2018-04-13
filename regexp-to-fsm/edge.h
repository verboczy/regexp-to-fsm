#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "node.h"
#include <list>

class Edge {
public:

    Edge();
    Edge(Node begin, Node end);

    Edge(Edge const& other);
    Edge& operator=(Edge const& rhs);

    Edge(Edge && other);
    Edge& operator=(Edge && rhs);

    ~Edge();

private:
    Node begin_node;
    Node end_node;

    //std::list<char> label_chars;
};

#endif
