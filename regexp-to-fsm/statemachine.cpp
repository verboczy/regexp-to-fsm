#include <iostream>

#include "statemachine.h"

StateMachine::StateMachine() {
    std::cout << "Default constructor - SM" << std::endl;
}

StateMachine::StateMachine(StateMachine const& other) {
    std::cout << "Copy ctor - SM" << std::endl;
    states = other.states;
}
StateMachine& StateMachine::operator=(StateMachine const& rhs) {
    std::cout << "Copy = - SM" << std::endl;

    if (this != &rhs) {
        states = rhs.states;
    }

    return *this;
}

StateMachine::StateMachine(StateMachine && other) noexcept {
    std::cout << "Move ctor - SM" << std::endl;
    states = std::move_if_noexcept(other.states);
}
StateMachine& StateMachine::operator=(StateMachine && rhs) noexcept {
    std::cout << "Move = - SM" << std::endl;

    if (this != &rhs) {
        states = std::move_if_noexcept(rhs.states);
    }

    return *this;
}

StateMachine::~StateMachine() {
    std::cout << "Destructor - SM" << std::endl;
}

void StateMachine::add_state(Node node, std::list<Edge> edges) {
    std::cout << "add_state" << std::endl;
    //std::pair<Node,std::list<Edge>>
    //auto a = make_pair(std::move(node), std::move(edges));
    states.insert(make_pair(std::move(node), std::move(edges)));
}

bool check(std::string expression) {



    return false;
}

