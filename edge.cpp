#include <iostream>

#include "edge.h"
#include "node.h"

Edge::Edge() { }

Edge::Edge(Node begin, Node end, char char_): begin_node{begin}, end_node{end}, label_char{char_} { }

Node Edge::get_end_node() const {
    return end_node;
}

char Edge::get_label_char() const {
    return label_char;
}
