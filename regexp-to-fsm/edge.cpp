#include <iostream>

#include "edge.h"
#include "node.h"

Edge::Edge() {
    std::cout << "Default constructor - E" << std::endl;
}

Edge::Edge(Node begin, Node end, std::list<char> chars): begin_node{begin}, end_node{end}, label_chars{chars} {
    std::cout << "Constructor - E" << std::endl;
}

Edge::Edge(Edge const& other) {
    std::cout << "Copy constructor - E" << std::endl;
    begin_node = other.begin_node;
    end_node = other.end_node;
    label_chars = other.label_chars;
}

Edge& Edge::operator=(Edge const& rhs) {
    std::cout << "Copy = - E" << std::endl;

    if (this != &rhs) {
        begin_node = rhs.begin_node;
        end_node = rhs.end_node;
        label_chars = rhs.label_chars;
    }

    return *this;
}

Edge::Edge(Edge && other) {
    std::cout << "Move constructor - E" << std::endl;
    begin_node = other.begin_node;
    end_node = other.end_node;
    label_chars = std::move_if_noexcept(other.label_chars); /// check this
}

Edge& Edge::operator=(Edge && rhs) {
    std::cout << "Move = - E" << std::endl;

    if (this != &rhs) {
        begin_node = rhs.begin_node;
        end_node = rhs.end_node;
        label_chars = std::move_if_noexcept(rhs.label_chars); /// check this
    }

    return *this;
}

Edge::~Edge() {
    std::cout << "Destructor - E" << std::endl;
}

Node Edge::get_end_node() const {
    return end_node;
}

std::list<char> Edge::get_label_chars() const {
    return label_chars;
}
