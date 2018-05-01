#include <iostream>

#include "edge.h"
#include "node.h"

Edge::Edge() { }

Edge::Edge(Node begin, Node end, char char_): begin_node{begin}, end_node{end}, label_char{char_} { }

Edge::Edge(Edge const& other) {
    begin_node = other.begin_node;
    end_node = other.end_node;
    label_char = other.label_char;
}

Edge& Edge::operator=(Edge const& rhs) {
    if (this != &rhs) {
        begin_node = rhs.begin_node;
        end_node = rhs.end_node;
        label_char = rhs.label_char;
    }
    return *this;
}

Edge::Edge(Edge && other) noexcept {
    begin_node = other.begin_node;
    end_node = other.end_node;
    label_char = std::move_if_noexcept(other.label_char);
}

Edge& Edge::operator=(Edge && rhs) noexcept {

    if (this != &rhs) {
        begin_node = rhs.begin_node;
        end_node = rhs.end_node;
        label_char = std::move_if_noexcept(rhs.label_char);
    }

    return *this;
}

Edge::~Edge() { }

Node Edge::get_end_node() const {
    return end_node;
}

char Edge::get_label_char() const {
    return label_char;
}
