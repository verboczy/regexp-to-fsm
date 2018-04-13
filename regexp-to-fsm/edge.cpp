#include <iostream>

#include "edge.h"
#include "node.h"

Edge::Edge() {
    std::cout << "Default constructor - E" << std::endl;
}

Edge::Edge(Node begin, Node end) {
    std::cout << "Constructor - E" << std::endl;
}

Edge::Edge(Edge const& other) {
    std::cout << "Copy constructor - E" << std::endl;
}

Edge& Edge::operator=(Edge const& rhs) {
    std::cout << "Copy = - E" << std::endl;
    return *this;
}

Edge::Edge(Edge && other) {
    std::cout << "Move constructor - E" << std::endl;
}
Edge& Edge::operator=(Edge && rhs) {
    std::cout << "Move = - E" << std::endl;
    return *this;
}

Edge::~Edge() {
    std::cout << "Destructor - E" << std::endl;
}
