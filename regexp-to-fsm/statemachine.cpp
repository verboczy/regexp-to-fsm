#include <iostream>
#include <queue>
#include <string>

#include "statemachine.h"

char epsilon = '@';

/// Add state to state machine, meaning a node and edges going out from the node
void StateMachine::add_state(Node node, std::list<Edge> edges) {
    states.insert( {node, edges} );
}

/// Returns the initial node - there is exactly one initial node is in each state machine
Node StateMachine::get_initial() const {
    for (auto iter = states.begin(); iter != states.end(); iter++) {
        if (iter->first.get_is_init()) {
            return iter->first;
        }
    }
    Node init;
    return init;
}

/// Adds an edge to the given node's edge list
void StateMachine::add_edge_to_list(Node node, Edge edge) {
    std::list<Edge> edge_list = states[node];
    edge_list.push_back(edge);
    states[node] = edge_list;
}

/// Check whether the given expression is matching on the state machine
bool StateMachine::check(std::string expression) const {
    Node initial_node = get_initial();
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
        }
        else {
            /// Get edges from the actual node
            auto edges = states.find(node);
            if (edges == states.end()) {
                /// The actual node was not found in the state machine
                continue;
            }
            /// Check which edge can we take
            for (auto edge : edges->second) {
                char character = edge.get_label_char();
                /// Add the end nodes of the edge, which can be taken
                if (str[0] == character || epsilon == character) {
                    Node next_node = edge.get_end_node();
                    std::string new_string = str;
                    if (str[0] == character) {
                        new_string.erase(0, 1);
                    }
                    node_queue.push(make_pair(next_node, new_string));
                }
            }
        }
    }
    return false;
}

/// Returns whether the state machine contains the given node
bool StateMachine::contains_node(Node node) {
    return states.find(node) != states.end();
}

/******************************STATEMACHINEBUILDER******************************/


size_t StateMachineBuilder::get_end_of_scope(std::string str, size_t startposition) {
    if (str[startposition] == '|') {
        startposition++;
    }
    if (str[startposition] != '(') {
        /// E.g. a|b*
        if (startposition+1 < str.length() && (str[startposition+1] == '*' || str[startposition+1] == '+')) {
            startposition++;
        }
        return startposition;
    }
    /// Else str[startposition] == '('
    int parenthesis_count = 1;
    for (size_t i = startposition + 1; i < str.length(); i++) {
        if (str[i] == '(') {
            parenthesis_count++;
        }
        else if (str[i] == ')') {
            parenthesis_count--;
            if (parenthesis_count == 0) {
                /// E.g. a|(dc)*
                if (i+1 < str.length() && str[i+1] == '*') {
                    i++;
                }
                return i;
            }
        }
    }

    throw std::invalid_argument("Invalid expression");
}

size_t StateMachineBuilder::get_start_of_scope(std::string str, size_t startposition) {
    if (str[startposition] == '|' || str[startposition] == '*') {
        startposition--;
    }
    if (str[startposition] != ')') {
        return startposition;
    }
    /// Else str[startposition] == ')'
    int parenthesis_count = 1;
    for (size_t i = startposition - 1; i >= 0; i--) {
        if (str[i] == ')') {
            parenthesis_count++;
        }
        else if (str[i] == '(') {
            parenthesis_count--;
            if (parenthesis_count == 0) {
                return i;
            }
        }
    }

    throw std::invalid_argument("Invalid expression");
}

std::string StateMachineBuilder::plustostar(std::string expression) {
    std::string new_expression = expression;
    size_t index = new_expression.find('+');
    while (index != std::string::npos) {
        size_t where_to_insert = get_start_of_scope(new_expression, index - 1);
        new_expression.replace(index, 1, "*");
        new_expression.insert(index, new_expression.substr(where_to_insert, index - where_to_insert));
        index = new_expression.find('+');
    }

    return new_expression;
}

std::unordered_set<std::string> StateMachineBuilder::nomoreor(std::string expression, std::unordered_set<std::string> withoutor) {

    if (expression.find('|') == std::string::npos) {
        withoutor.insert(expression);
        return withoutor;
    }

    size_t pipe_position = expression.find('|');
    /// Delete the end
    size_t end_position = get_end_of_scope(expression, pipe_position + 1);
    std::string no_end = expression;
    /// erase(start, count) - [start, start + count]
    no_end.erase(pipe_position, end_position - pipe_position + 1);

    withoutor = nomoreor(no_end, withoutor);

    /// Delete the start
    size_t start_position = get_start_of_scope(expression, pipe_position - 1);
    std::string no_start = expression;
    no_start.erase(start_position, pipe_position - start_position + 1);

    withoutor = nomoreor(no_start, withoutor);

    return withoutor;
}

bool StateMachineBuilder::is_node_final(std::string expression) {
    int paranthesis_count = 0;
    for (size_t i = 0; i < expression.length(); i++) {
        if (isalpha(expression[i]) && paranthesis_count == 0) {
            if (i + 1 < expression.length() && expression[i + 1] == '*') {
                /// Looks good at this point, but it is not know what comes after it.
            }
            else {
                /// Last character was an alphabetic character or the next character is not *.
                return false;
            }
        }
        else if (expression[i] == '(') {
            paranthesis_count++;
        }
        else if (expression[i] == ')') {
            paranthesis_count--;
            if (paranthesis_count == 0) {
                if (i + 1 < expression.length() && expression[i + 1] == '*') {
                    /// Looks good at this point, but it is not know what comes after it.
                }
                else {
                    /// If ) is the last character or not a * is after it then it cannot be final.
                    return false;
                }
            }
        }
    }

    return true;
}


std::string StateMachineBuilder::nomoreunusesparenthesis(std::string expression) {
    int opener = 0;
    int closer = 0;
    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            opener++;
        }
        else if (expression[i] == ')') {
            closer++;
        }
    }
    if (opener != closer) {
        throw std::invalid_argument("Something is not right with parenthesis");
    }
    size_t search_start_position = 0;
    size_t position;
    while ((position = expression.find('(', search_start_position)) != std::string::npos) {
        std::string temp_copy = expression;
        int parenthesis_count = 1;
        size_t i = position + 1;
        while (parenthesis_count != 0 && i < expression.length()) {
            if (expression[i] == '(') {
                parenthesis_count++;
            }
            else if (expression[i] == ')') {
                parenthesis_count--;
                if (parenthesis_count == 0) {
                    /// (asd)* <-- this is not unused
                    if (i + 1 < expression.length() && expression[i + 1] == '*') {
                        /// a(a)* <-- this is unused, has to be deleted
                        if (i - position == 2) {
                            /// First delete unused )
                            expression.erase(i, 1);
                            /// Then delete unused (
                            expression.erase(position, 1);
                        }
                        else {
                            search_start_position++;
                        }
                    }
                    /// (asd), (asd)asd <-- these are unused
                    else {
                        /// First delete unused )
                        expression.erase(i, 1);
                        /// Then delete unused (
                        expression.erase(position, 1);
                        /// Search start should remain the same place
                    }
                }
            }
            i++;
        }
    }

    return expression;
}


std::list<Node> StateMachineBuilder::buildSubStateMachine(StateMachine& sm, std::string expression, std::list<Node> initial_node_list,
                          std::list<Node>& original_node_list, bool is_it_final) {

    Node previous_node = initial_node_list.back();
    std::list<Node> node_list;

    std::list<Node> list_of_end_nodes;

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ')' || expression[i] == '*') {
            continue;
        }

        if (expression[i] == '(') {
            size_t start_position = i;
            int actual_size = expression.length() - start_position;
            std::string actual_expression = expression.substr(start_position, actual_size);
            Node sub_sm_initial_node{false, false};

            size_t end_position = get_end_of_scope(expression, start_position);
            start_position++;
            end_position--;
            int size = end_position - start_position;
            std::string subexpression = expression.substr(start_position, size);
            bool is_subexpression_final = is_node_final(subexpression);
            if (is_it_final && is_node_final(actual_expression) && is_subexpression_final) {
                sub_sm_initial_node.set_as_final();
            }

            Edge edge{previous_node, sub_sm_initial_node, epsilon};
            sm.add_edge_to_list(previous_node, edge);

            for (Node node : node_list) {
                Edge edge{node, sub_sm_initial_node, epsilon};
                sm.add_edge_to_list(node, edge);
            }
            initial_node_list.push_back(sub_sm_initial_node);
            auto nl = buildSubStateMachine(sm, subexpression, initial_node_list, original_node_list, is_node_final(actual_expression));
            for (auto n : nl) {
                node_list.push_back(n);
            }
            i = end_position;
        }
        else if (i + 1 >= expression.length()) {
            Node final_node{false, is_it_final};

            Edge edge{previous_node, final_node, expression[i]};
            if (sm.contains_node(previous_node)) {
                sm.add_edge_to_list(previous_node, edge);
            }
            else {
                std::list<Edge> edge_list = { edge };
                sm.add_state(previous_node, edge_list);
            }
            original_node_list.push_back(final_node);
            list_of_end_nodes.push_back(final_node);

            for (Node node : node_list) {
                Edge edge{node, final_node, expression[i]};
                sm.add_edge_to_list(node, edge);
            }
            std::list<Edge> edge_list;
            for (Node init_node : initial_node_list) {
                Edge to_first_node{final_node, init_node, epsilon};
                edge_list.push_back(to_first_node);
            }
            sm.add_state(final_node, edge_list);
        }
        else if (expression[i + 1] == '*') {
            Node actual_node{false, false};
            std::string subexpression = expression.substr(i, expression.length() - i);
            if (is_node_final(subexpression)) {
                if (is_it_final) {
                    actual_node.set_as_final();
                }
                std::list<Edge> edge_list;
                for (Node init_node : initial_node_list) {
                    Edge edge{actual_node, init_node, epsilon};
                    edge_list.push_back(edge);
                }
                sm.add_state(actual_node, edge_list);
                original_node_list.push_back(actual_node);
                list_of_end_nodes.push_back(actual_node);
            }

            Edge edge{previous_node, actual_node, expression[i]};
            if (sm.contains_node(previous_node)) {
                sm.add_edge_to_list(previous_node, edge);
            }
            else {
                std::list<Edge> edge_list = { edge };
                sm.add_state(previous_node, edge_list);
            }

            for (Node node : node_list) {
                Edge edge{node, actual_node, expression[i]};
                sm.add_edge_to_list(node, edge);
            }
            Edge loop_edge{actual_node, actual_node, expression[i]};
            if (sm.contains_node(actual_node)) {
                sm.add_edge_to_list(actual_node, loop_edge);
            }
            else {
                std::list<Edge> edge_list = { loop_edge };
                sm.add_state(actual_node, edge_list);
            }
            node_list.push_back(actual_node);
        }
        else {
            Node actual_node{false, false};
            size_t start_position = i + 1;
            std::string subexpression = expression.substr(start_position, expression.length() - start_position);
            if (is_node_final(subexpression)) {
                if (is_it_final) {
                    actual_node.set_as_final();
                }
                std::list<Edge> edge_list;
                for (Node init_node : initial_node_list) {
                    Edge edge{actual_node, init_node, epsilon};
                    edge_list.push_back(edge);
                }
                sm.add_state(actual_node, edge_list);
                original_node_list.push_back(actual_node);
                list_of_end_nodes.push_back(actual_node);
            }

            Edge edge{previous_node, actual_node, expression[i]};
            if (sm.contains_node(previous_node)) {
                sm.add_edge_to_list(previous_node, edge);
            }
            else {
                std::list<Edge> edge_list = { edge };
                sm.add_state(previous_node, edge_list);
            }

            for (Node node : node_list) {
                Edge edge{node, actual_node, expression[i]};
                sm.add_edge_to_list(actual_node, edge);
            }
            previous_node = actual_node;
            node_list.clear();
        }
    }
    return list_of_end_nodes;
}

StateMachine StateMachineBuilder::buildSingleStateMachine(std::string expression) {
    StateMachine sm;
    Node initial_node{true, false};
    if (is_node_final(expression)) {
        initial_node.set_as_final();
    }

    std::list<Node> node_list;
    Node previous_node = initial_node;

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ')' || expression[i] == '*') {
            continue;
        }

        if (expression[i] == '(') {
            size_t start_position = i;
            int actual_size = expression.length() - start_position;
            std::string actual_expression = expression.substr(start_position, actual_size);
            Node sub_sm_initial_node{false, false};

            size_t end_position = get_end_of_scope(expression, start_position);
            start_position++;
            end_position--;
            int size = end_position - start_position;
            std::string subexpression = expression.substr(start_position, size);
            bool is_subexpression_final = is_node_final(subexpression);
            if (is_node_final(actual_expression) && is_subexpression_final) {
                sub_sm_initial_node.set_as_final();
            }

            {
                Edge edge{previous_node, sub_sm_initial_node, epsilon};
                sm.add_edge_to_list(previous_node, edge);
            }
            for (Node node : node_list) {
                Edge edge{node, sub_sm_initial_node, epsilon};
                sm.add_edge_to_list(node, edge);
            }

            std::list<Node> init_node_list = { sub_sm_initial_node };
            auto nl = buildSubStateMachine(sm, subexpression, init_node_list, node_list, is_node_final(actual_expression));
            for (auto n : nl) {
                node_list.push_back(n);
            }
            i = end_position;
        }
        else if (i + 1 >= expression.length()) {
            Node final_node{false, true};
            {
                Edge edge{previous_node, final_node, expression[i]};
                if (sm.contains_node(previous_node)) {
                    sm.add_edge_to_list(previous_node, edge);
                }
                else {
                    std::list<Edge> edge_list = { edge };
                    sm.add_state(previous_node, edge_list);
                }
            }
            for (Node node : node_list) {
                Edge edge{node, final_node, expression[i]};
                sm.add_edge_to_list(node, edge);
            }
            Edge no_matter_edge{final_node, final_node, '.'};
            std::list<Edge> edge_list = { no_matter_edge };
            sm.add_state(final_node, edge_list);
        }
        else if (expression[i + 1] == '*') {
            Node actual_node{false, false};
            std::string subexpression = expression.substr(i, expression.length() - i);
            if (is_node_final(subexpression)) {
                actual_node.set_as_final();
            }
            {
                Edge edge{previous_node, actual_node, expression[i]};
                if (sm.contains_node(previous_node)) {
                    sm.add_edge_to_list(previous_node, edge);
                }
                else {
                    std::list<Edge> edge_list = { edge };
                    sm.add_state(previous_node, edge_list);
                }
            }
            for (Node node : node_list) {
                Edge edge{node, actual_node, expression[i]};
                sm.add_edge_to_list(node, edge);
            }
            Edge loop_edge{actual_node, actual_node, expression[i]};
            std::list<Edge> edge_list = { loop_edge };
            sm.add_state(actual_node, edge_list);
            node_list.push_back(actual_node);
        }
        else {
            Node actual_node{false, false};
            size_t start_position = i + 1;
            std::string subexpression = expression.substr(start_position, expression.length() - start_position);
            if (is_node_final(subexpression)) {
                actual_node.set_as_final();
            }

            Edge edge{previous_node, actual_node, expression[i]};
            if (sm.contains_node(previous_node)) {
                sm.add_edge_to_list(previous_node, edge);
            }
            else {
                std::list<Edge> edge_list = { edge };
                sm.add_state(previous_node, edge_list);
            }

            for (Node node : node_list) {
                Edge edge{node, actual_node, expression[i]};
                sm.add_edge_to_list(node, edge);
            }
            previous_node = actual_node;
            node_list.clear();
        }
    }
    return sm;
}

void StateMachineBuilder::buildStateMachine(std::string expression) {
    std::list<StateMachine> sm_list;
    std::unordered_set<std::string> expression_set;
    expression_set = nomoreor(expression, expression_set);
    for (std::string exp : expression_set) {
        std::string exp_no_plus = plustostar(exp);
        std::string exp_final = nomoreunusesparenthesis(exp_no_plus);
        StateMachine sm = buildSingleStateMachine(exp_final);
        sm_list.push_back(sm);
    }

    statemachine_list = std::move_if_noexcept(sm_list);
}

bool StateMachineBuilder::check(std::string expression) {
    if (statemachine_list.empty()) {
        throw std::invalid_argument("Create a state machine before check!");
    }

    for (StateMachine sm : statemachine_list) {
        if (sm.check(expression)) {
            return true;
        }
    }
    return false;
}
