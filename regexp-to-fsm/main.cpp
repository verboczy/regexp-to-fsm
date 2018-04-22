#include <iostream>
#include <unordered_set>

#include "statemachine.h"
#include "node.h"

using namespace std;




std::list<std::string> resolveOR(std::string original, std::list<std::string> result_list) {

    /// If no more | in the expression put the expression into the result and return
    //if (NO MORE |) {

    //}

    /// Otherwise, create two new

    //result_list =

    return result_list;
}

/// a*
void test1() {
    Node node{true, true};

    std::list<char> chars = { 'a' };
    Edge edge{node, node, chars};
    std::list<Edge> edges = { edge };
    std::cout << "edge size " << edges.size() << std::endl;

    StateMachine statemachine;
    statemachine.add_state(node, edges);
    statemachine.print_elements();

    std::string user_input;
    std::cin >> user_input;

    while (user_input != "exit") {
        bool result = statemachine.check(user_input);
        std::cout << user_input << " is " << result << std::endl;
        std::cin >> user_input;
    }
}

/// ab*a
void test2() {
    Node node1{true, false};
    Node node2{false, false};

    std::list<char> chars1 = { 'a' };
    Edge edge1{node1, node2, chars1};
    std::list<Edge> edges1 = { edge1 };

    StateMachine stateMachine;
    stateMachine.add_state(node1, edges1);

    Node node3{false, true};

    std::list<char> chars2 = { 'b' };
    Edge edge2{node2, node2, chars2};

    std::list<char> chars3 = { 'a' };
    Edge edge3{node2, node3, chars3};

    std::list<Edge> edges2 = { edge2, edge3 };

    stateMachine.add_state(node2, edges2);

    std::string user_input;
    std::cin >> user_input;

    while (user_input != "exit") {
        bool result = stateMachine.check(user_input);
        std::cout << user_input << " is " << result << std::endl;
        std::cin >> user_input;
    }
}
/*
StateMachine createSM_old(std::string expression) {

    if (expression.length() < 1) {
        throw std::length_error("Regular expression is too short");
    }

    StateMachine sm;

    /// Create initial node
    Node init_node{true, false};
    Node previous_node = init_node;
    for (size_t i = 0; i < expression.length() - 1; i++) {
        if (expression[i] == "*") {
            continue;
        }
        /// Create another node
        Node actual_node{false, false};
        /// Create char list
        std::list<char> chars = { expression[i] };
        /// Create edge
        Edge edge{previous_node, actual_node, chars};
        /// Create edge list
        std::list<Edge> edges = { edge };

        if (expression[i + 1] == "*") {
            Edge loop_edge{actual_node, actual_node, chars};

            sm.add_state(actual_node, )
        }

        /// Add edge and node to state machine
        sm.add_state(previous_node, edges);

        previous_node = actual_node;
    }
    Node end_node{false, true};
    std::list<char> chars = { expression[expression.length() - 1] };
    Edge edge{previous_node, end_node, chars};
    std::list<Edge> edges = { edge };

    sm.add_state(previous_node, edges);

    std::list<Edge> empty_edges;
    sm.add_state(end_node, empty_edges);

    return sm;
}


StateMachine createSM(std::string expression) {

    if (expression.length() < 1) {
        throw std::length_error("Regular expression is too short");
    }

    StateMachine sm;

    /// Length of the regular expression
    size_t length = expression.length();

    /// Create initial node
    Node init_node{true, false};
    Node next_node = init_node;
    for (size_t i = 0; i < length - 1; i++) {
        Node actual_node = next_node;
        /// Create char list
        std::list<char> chars = { expression[i] };
        /// Create the list of edges from the actual node
        std::list<Edge> edges;

        if (expression[i + 1] == '*') {
            /// Create loop edge
            Edge loop_edge{actual_node, actual_node, chars};
            /// Add loop edge to the edge list
            edges.push_back(loop_edge);

            if (i + 2 >= length) {
                actual_node.set_as_final();
                sm.add_state(actual_node, edges);
            }
            else {
                Node new_node{false, false};

            }
        }
        /// Create another node
        Node actual_node{false, false};
        /// Create edge
        Edge edge{previous_node, actual_node, chars};
        /// Create edge list
        std::list<Edge> edges = { edge };

        if (expression[i + 1] == "*") {
            Edge loop_edge{actual_node, actual_node, chars};

            sm.add_state(actual_node, )
        }

        /// Add edge and node to state machine
        sm.add_state(previous_node, edges);

        previous_node = actual_node;
    }
    Node end_node{false, true};
    std::list<char> chars = { expression[expression.length() - 1] };
    Edge edge{previous_node, end_node, chars};
    std::list<Edge> edges = { edge };

    sm.add_state(previous_node, edges);

    std::list<Edge> empty_edges;
    sm.add_state(end_node, empty_edges);

    return sm;
}
*/

size_t get_end_of_scope(std::string str, size_t startposition) {
    if (str[startposition] == '|') {
        startposition++;
    }
    if (str[startposition] != '(') {
        /// E.g. a|b*
        if (startposition+1 < str.length() && str[startposition+1] == '*') {
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

size_t get_start_of_scope(std::string str, size_t startposition) {
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

std::string plustostar(std::string expression) {
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

std::unordered_set<std::string> nomoreor(std::string expression, std::unordered_set<std::string> withoutor) {

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
    //std::cout << "Without end: " << no_end << std::endl;

    withoutor = nomoreor(no_end, withoutor);

    /// Delete the start
    size_t start_position = get_start_of_scope(expression, pipe_position - 1);
    std::string no_start = expression;
    no_start.erase(start_position, pipe_position - start_position + 1);
    //std::cout << "Without start: " << no_start << std::endl;

    withoutor = nomoreor(no_start, withoutor);

    return withoutor;
}

int main()
{
    std::string cica = "cica";
    cica.insert(0, "kis");
    std::cout << cica << std::endl;

    std::string e6 = plustostar("q*w*|d(c|(ab)*)+aaaabs+ac+(dc*a)+");

    std::unordered_set<std::string> withoutor;
    std::string e1 = "(a(b|s))|b";
    std::string e2 = "aab(cd)*|(ef)*g*a*";
    std::string e3 = "a*|b*";
    std::string e4 = "a*";
    std::string e5 = "a|b|c|d|e*|(cd)|(kjl)*|(q*w*e*)*";
    withoutor = nomoreor(e6, withoutor);

    for (auto str : withoutor) {
        std::cout << str << std::endl;
    }
    //std::string asd = "asd";
    //std::cout << asd.find('|') << ", " << std::string::npos << std::endl;

    //std::string expr = "(a(b|s))|b";
    //std::cout << expr.erase(4, 2) << std::endl;

    /*
    size_t pipe_position = expr.find('|');
    std::cout << pipe_position << std::endl;
    size_t start_position = get_start_of_scope(expr, pipe_position - 1);
    std::cout << start_position << std::endl;
    std::cout << expr.erase(start_position, pipe_position + 1) << std::endl;
    */
    /*
    size_t start_position = expr.find('|');
    std::cout << start_position << std::endl;
    size_t end_position = get_end_of_scope(expr, start_position + 1);
    std::cout << end_position << std::endl;
    std::cout << expr.erase(start_position, end_position) << std::endl;
    */


    //test2();
/*
    StateMachine sm = createSM("abc");

    std::string user_input;
    std::cin >> user_input;

    while (user_input != "exit") {
        bool result = sm.check(user_input);
        std::cout << user_input << " is " << result << std::endl;
        std::cin >> user_input;
    }


    StateMachine sm{};
    StateMachine sm2 = sm;
    StateMachine sm3 = std::move(sm);
    sm3 = sm2;
    sm = std::move(sm2);

    Node n1{false, false};
    Node n2{true, false};
   // Node n1{};
   // Node n2{};

   std::list<char> chars = { 'a', 'b', 'c', 'd', 'e' };

    Edge e{};
    Edge e2{n1, n2, chars};
    Edge e3 = e;
    e = e2;
    Edge e4 = std::move(e3);
    e2 = std::move(e);

    Node node{false, false};
//    Node node{};
    std::list<Edge> edges;
    sm.add_state(node, edges);
    */

    return 0;
}
