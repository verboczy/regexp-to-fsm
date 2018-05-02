#include <iostream>

#include "node.h"

int Node::max_id = 0;

Node::Node() {
    is_init = false;
    is_final = false;
    max_id++;
    id = max_id;
}

Node::Node(bool initial, bool fin): is_init{initial}, is_final{fin} {
    max_id++;
    id = max_id;
}

void Node::set_as_final() {
    is_final = true;
}

bool Node::get_is_init() const {
    return is_init;
}

bool Node::get_is_final() const {
    return is_final;
}

bool Node::operator< (Node const& rhs) const {
    return this->id < rhs.id;
}
