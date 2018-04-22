#include <iostream>
#include <queue>
#include <string>

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

/// Add state to state machine, meaning a node and edges from it
void StateMachine::add_state(Node node, std::list<Edge> edges) {
    std::cout << "add_state" << std::endl;
    //std::pair<Node,std::list<Edge>>
    //auto a = make_pair(std::move(node), std::move(edges));

    //states.insert(make_pair(std::move(node), std::move(edges)));
    //states.insert(make_pair(node, edges));
    states.insert( {node, edges} );
    //std::cout << edges.size() << " vs " << states[node].size() << std::endl;
}

void StateMachine::print_elements() {
    for (auto elem : states) {
        std::cout << elem.first.get_is_init() << " - " << elem.second.size() << std::endl;
    }
}

/// Returns the initial node
/// There is exactly one initial node is in each state machine
Node StateMachine::get_initial() {

    for (auto iter = states.begin(); iter != states.end(); iter++) {
        if (iter->first.get_is_init()) {
           // std::cout << "INITIAL FOUND" << std::endl;
            auto edges = states[iter->first];
            //std::cout << edges.size() << std::endl;
            return iter->first;
        }
    }

    Node init;
    return init;
}

void StateMachine::add_edge_to_list(Node node, Edge edge) {
    ststates[node]
}

bool StateMachine::check(std::string expression) {

    Node initial_node = get_initial();
    //std::cout << initial_node.get_is_init() << std::endl;

    std::queue<std::pair<Node, std::string>> node_queue;
    node_queue.push(make_pair(initial_node, expression));

    while (!node_queue.empty()) {
        Node node = node_queue.front().first;
        std::string str = node_queue.front().second;
        node_queue.pop();

        if (str.empty()) {
            if (node.get_is_final()) {
                /// There are no character left and the state is accepting, so the word is good for the regular expression.
                return true;
            }
            //std::cout << "STR IS EMPTY, BUT NOT FINAL" << std::endl;
        }
        else {
           // std::cout << "STR IS NOT EMPTY" << std::endl;
            /// get edges of the actual node
            auto edges = states[node];
           // std::cout << edges.size() << std::endl;

            /// check which edge can we take
            for (auto edge : edges) {
                //std::cout << "ITERATE OVER EDGES" << std::endl;
                auto chars = edge.get_label_chars();
                for (auto character : chars) {
                   // std::cout << "ITERATE OVER CHARACTERS" << std::endl;
                    /// add the end nodes of the good edges
                    if (str[0] == character) {
                       // std::cout << "ADD NEW NODE TO THE QUEUE" << std::endl;
                        Node next_node = edge.get_end_node();
                        std::string new_string = str;
                        new_string.erase(0, 1);
                        node_queue.push(make_pair(next_node, new_string));
                    }
                }
            }
        }
    }

    return false;
}

