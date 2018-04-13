#include <iostream>

#include "statemachine.h"

StateMachine::StateMachine() {
    std::cout << "Default constructor - SM" << std::endl;
}

StateMachine::StateMachine(StateMachine const& other) {
    std::cout << "Copy ctor - SM" << std::endl;
}
StateMachine& StateMachine::operator=(StateMachine const& rhs) {
    std::cout << "Copy = - SM" << std::endl;
    return *this;
}

StateMachine::StateMachine(StateMachine && other) noexcept {
    std::cout << "Move ctor - SM" << std::endl;
}
StateMachine& StateMachine::operator=(StateMachine && rhs) noexcept {
    std::cout << "Move = - SM" << std::endl;
    return *this;
}

StateMachine::~StateMachine() {
    std::cout << "Destructor - SM" << std::endl;
}

bool StateMachine::add_state(Node node, std::list<Edge> edges) {
    std::cout << "add_state" << std::endl;
    return false;
}
