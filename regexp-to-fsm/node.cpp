#include <iostream>

#include "node.h"

int Node::max_id = 0;

Node::Node() {
    //std::cout << "Default constructor - N" << std::endl;
    is_init = false;
    is_final = false;
    max_id++;
    id = max_id;
}

Node::Node(bool initial, bool fin): is_init{initial}, is_final{fin} {
    //std::cout << "Constructor - N" << std::endl;
    max_id++;
    id = max_id;
}

Node::Node(Node const& other) {
   // std::cout << "Copy constructor - N" << std::endl;
    this->is_init = other.is_init;
    this->is_final = other.is_final;
    this->id = other.id;
}
Node& Node::operator=(Node const& rhs) {
   // std::cout << "Copy = - N" << std::endl;

    if (this != &rhs) {
        this->is_init = rhs.is_init;
        this->is_final = rhs.is_final;
        this->id = rhs.id;
    }

    return *this;
}

Node::Node(Node && other) {
    //std::cout << "Move constructor - N" << std::endl;
    this->is_init = other.is_init;
    this->is_final = other.is_final;
    this->id = other.id;
}

Node& Node::operator=(Node && rhs) {
    //std::cout << "Move = - N" << std::endl;

    if (this != &rhs) {
        this->is_init = rhs.is_init;
        this->is_final = rhs.is_final;
        this->id = rhs.id;
    }

    return *this;
}

Node::~Node() {
    //std::cout << "Destructor - N" << std::endl;
}

void Node::set_as_init() {
    is_init = true;
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
