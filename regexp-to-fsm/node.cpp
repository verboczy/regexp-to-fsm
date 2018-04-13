#include <iostream>

#include "node.h"

Node::Node() {
    std::cout << "Default constructor - N" << std::endl;
}

Node::Node(bool initial, bool fin) {
    std::cout << "Constructor - N" << std::endl;
}

Node::Node(Node const& other) {
    std::cout << "Copy constructor - N" << std::endl;
}
Node& Node::operator=(Node const& rhs) {
    std::cout << "Copy = - N" << std::endl;
    return *this;
}

Node::Node(Node && other) {
    std::cout << "Move constructor - N" << std::endl;
}
Node& Node::operator=(Node && rhs) {
    std::cout << "Move = - N" << std::endl;
    return *this;
}

Node::~Node() {
    std::cout << "Destructor - N" << std::endl;
}

void Node::set_as_init() {
    is_init = true;
}

void Node::set_as_final() {
    is_final = true;
}
