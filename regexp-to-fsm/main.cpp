#include <iostream>
#include <unordered_set>

#include "statemachine.h"
#include "node.h"

using namespace std;

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
    stateMachine.print_statemachine();
}

/// a*b
void test3() {
    Node node1{true, false};
    Node node2{false, true};

    std::list<char> chars1 = { 'a' };
    std::list<char> chars2 = { 'b' };
    Edge edge1{node1, node1, chars1};
    Edge edge2{node1, node2, chars2};
    std::list<Edge> edges1 = { edge1 };

    StateMachine stateMachine;
    stateMachine.add_state(node1, edges1);
    stateMachine.add_edge_to_list(node1, edge2);
    std::string user_input;
    std::cin >> user_input;

    while (user_input != "exit") {
        bool result = stateMachine.check(user_input);
        std::cout << user_input << " is " << result << std::endl;
        std::cin >> user_input;
    }
    stateMachine.print_statemachine();
}

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

    std::cout << "itt lesz exception?" << std::endl;
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

bool is_node_final(std::string expression) {
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

/// UNDER CONSTRUCTION
bool back_edge_needed(std::string expression) {
    if (expression.length() <= 1) {
        return true;
    }
    //std::cout << "expression: " << expression << std::endl;
    //std::string subexpression = expression.substr(1, expression.length() - 1);
    //std::cout << "expression: " << subexpression << std::endl;
    int paranthesis_count = 0;
    for (size_t i = 0; i < expression.length(); i++) {
        if (isalpha(expression[i]) && paranthesis_count == 0) {
            if (i + 1 < expression.length() && expression[i + 1] == '*') {
                /// Looks good at this point, but it is not know what comes after it.
            }
            else {
                if (i != 0) {
                    /// Last character was an alphabetic character or the next character is not *.
                    return false;
                }
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


std::string nomoreunusesparenthesis(std::string expression) {
    size_t search_start_position = 0;
    size_t position;
    while ((position = expression.find('(', search_start_position)) != std::string::npos) {
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

void buildSubStateMachine(StateMachine& sm, Node actual_node, Node first_node, std::string expression, size_t start_index, size_t end_index) {
    /// None of the sub state machine's node can be final
    /// If it seems like it is final, then it must have an edge to the first node
    //Node first_node = actual_node;
    start_index++;

    /// Here, only the substring is needed: e.g. a(ab(ac)*b)* --> ab(ac)*b
    std::string subexpression = expression.substr(start_index , end_index - start_index - 1);
    std::cout << "subSM " << subexpression << std::endl;
    std::list<Node> node_list;
    for (size_t i = 0; i < subexpression.length(); i++) {
        std::cout << "i: " << i << std::endl;
        if (subexpression[i] == '*') {
            continue;
        }

        /// Create character and edge list
        std::list<char> character_list = { subexpression[i] };
        std::list<Edge> edge_list;

        /// Add edges from older nodes to the actual, possible because star means 0..*
        for (Node node : node_list) {
            Edge new_edge{node, actual_node, character_list};
            sm.add_edge_to_list(node, new_edge);
        }

        Node next_node{false, false};
        std::string subsubexpression = subexpression.substr(i + 1,subexpression.length() - i - 1);

        /// recursive call, for embedded expressions
        if (subexpression[i] == '(') {
            std::cout << "sub(" << std::endl;
            size_t start_index = i;
            size_t end_index = get_end_of_scope(subexpression, start_index);
            buildSubStateMachine(sm, actual_node, first_node, subexpression, start_index, end_index);


            /// Push actual to node_list - because it must have a star at the end
            node_list.push_back(actual_node);
            /// Set i to end_index
            i = end_index;
            /// Set actual to next
            actual_node = next_node;
            Edge empty_edge;
            edge_list.push_back(empty_edge);
            std::cout << "returned from sub, still in sub" << std::endl;
        }
        /// no more character after this
        else if (i + 1 >= subexpression.length()) {
            std::cout << "sub-nomore" << std::endl;
            /// edge back to first node
            Edge edge{actual_node, first_node, character_list};
            edge_list.push_back(edge);
        }
        /// next character is *
        else if (subexpression[i+1] == '*') {
            std::cout << "sub*" << std::endl;
            /// If final, edge back to first node
            if (back_edge_needed(subsubexpression)) {
                Edge edge{actual_node, first_node, character_list};
                edge_list.push_back(edge);
            }
            /// Add a loop edge to the state machine
            Edge loop_edge{actual_node, actual_node, character_list};
            edge_list.push_back(loop_edge);
            /// Store this node in the list, for edges coming from this, which cannot be seen now
            node_list.push_back(actual_node);

        }
        /// next character is alphabetic
        else {//if (isalpha(subexpression[i + 1])) {
            std::cout << "sub else: " << subsubexpression << " is final: " << back_edge_needed(subsubexpression) << std::endl;
            /// If final, edge back to first node
            if (back_edge_needed(subsubexpression)) {
                Edge edge{actual_node, first_node, character_list};
                edge_list.push_back(edge);
            }
            /// Add node, with edge to state machine
            Edge edge{actual_node, next_node, character_list};
            edge_list.push_back(edge);
            /// Clear the node list
            node_list.clear();
        }

        sm.add_state(actual_node, edge_list);
        std::cout << "ez meg ok?" << std::endl;
        //sm.print_statemachine();
        std::cout << "ez meg ok?" << std::endl;
        actual_node = next_node;
    }

    std::cout << "Return from sub" << std::endl;
}

Node createNode(std::string expression, size_t start_index) {
    Node next_node{false, false};
    /// Set next node to final, if needed
    //std::string subexpression;
    //if (start_index > expression.length()) {
    //    std::string subexpression = expression.substr(expression.length(), 1);
    //}
    std::string subexpression = expression.substr(start_index, expression.length() - start_index);

    std::cout << "Subexpression: " << subexpression << std::endl;
    if (is_node_final(subexpression)) {
        next_node.set_as_final();
    }

    return next_node;
}

StateMachine buildStateMachine(std::string expression) {

    StateMachine sm;

    Node init_node{true, false};
    if (is_node_final(expression)) {
        init_node.set_as_final();
    }

    Node actual_node = init_node;
    std::list<Node> node_list;

    for (size_t i = 0; i < expression.length(); i++) {
        /// Skip non-alphabetic characters
        if (expression[i] == '*' || expression[i] == ')') {
            continue;
        }

        bool node_list_has_element = !node_list.empty();

        if (node_list_has_element && i + 1 >= expression.length()) {
            actual_node.set_as_final();
        }

        /// Create character and edge list
        std::list<char> character_list = { expression[i] };
        std::list<Edge> edge_list;


        /// Add edges from older nodes to the actual, possible because star means 0..*
        for (Node node : node_list) {
            //std::cout << "Node list visit: " << character_list.front() << std::endl;
            Edge new_edge{node, actual_node, character_list};
            sm.add_edge_to_list(node, new_edge);
        }
/*
        Node next_node{false, false};
        /// Set next node to final, if needed
        std::string subexpression = expression.substr(i + 1, expression.length() - i); /// ez nem az igazi amikor csillag van
        std::cout << "(no more)Subexpression: " << subexpression << std::endl;
        if (is_node_final(subexpression)) {
            next_node.set_as_final();
        }
*/
        if (expression[i] == '(') {
            size_t start_index = i;
            size_t end_index = get_end_of_scope(expression, start_index);
            buildSubStateMachine(sm, actual_node, actual_node, expression, start_index, end_index);

            std::cout << "asd Returned from sub" << std::endl;
            /// Push actual to node_list - because it must have a star at the end
            node_list.push_back(actual_node);
            /// Set i to end_index
            i = end_index;
            /// Set actual to next
            actual_node = createNode(expression, i + 2); /// TODO
        }

        /// No more character after this
        else if (i + 1 >= expression.length()) {
/*
            Node next_node{false, false};
            Edge edge{actual_node, next_node, character_list};
            edge_list.push_back(edge);
*/
            if (node_list_has_element) {
                /// This is the final node
                actual_node.set_as_final();
                std::cout << "asdasdasdasdasdasasadasdad" << std::endl;

                Edge empty_edge;
                std::list<Edge> empty_list = { empty_edge };
                sm.add_state(actual_node, empty_list);

            }
            else {
                std::cout << "ez is lefutna?" << std::endl;
                /// Need a final node and edge to reach it
                Node next_node{false, true};
                Edge edge{actual_node, next_node, character_list};
                edge_list.push_back(edge);
                sm.add_state(actual_node, edge_list);

                Edge empty_edge;
                std::list<Edge> empty_list = { empty_edge };
                sm.add_state(next_node, empty_list);

            }


            //sm.print_statemachine();
        }
        /// There is at least one more character
        /// Let's see if it is *
        else if (expression[i + 1] == '*') {
            Node next_node = createNode(expression, i + 2); /// i + 2 is good, because i + 1 < length, so i + 2 cannot be > length
            /// Add a loop edge to the state machine
            Edge loop_edge{actual_node, actual_node, character_list};
            edge_list.push_back(loop_edge);
            sm.add_state(actual_node, edge_list);
            //sm.print_statemachine();
            /// Store this node in the list, for edges coming from this, which cannot be seen now
            node_list.push_back(actual_node);
            actual_node = next_node;
        }
        /// or is it an alphabetic character?
        else {//if (isalpha(expression[i + 1])) {
            Node next_node = createNode(expression, i + 1);
            /// Add node, with edge to state machine
            Edge edge{actual_node, next_node, character_list};
            edge_list.push_back(edge);
            sm.add_state(actual_node, edge_list);
            //sm.print_statemachine();
            /// Clear the node list
            node_list.clear();
            actual_node = next_node;
        }
    }

    return sm;
}

void test_nomoreunusedparenthesis() {
    std::string ex1 = "aaa";
    //ex1 = nomoreunusesparenthesis(ex1);
    std::cout << ex1 << " - " << nomoreunusesparenthesis(ex1) << std::endl;
    std::string ex2 = "(a)aa";
    //ex2 = nomoreunusesparenthesis(ex2);    std::cout << ex2 << " - " << nomoreunusesparenthesis(ex2) << std::endl;
    std::string ex3 = "a(a)a";
    //ex3 = nomoreunusesparenthesis(ex3);
    std::cout << ex3 << " - " << nomoreunusesparenthesis(ex3) << std::endl;
    std::string ex4 = "aa(a)";
    //ex4 = nomoreunusesparenthesis(ex4);
    std::cout << ex4 << " - " << nomoreunusesparenthesis(ex4) << std::endl;
    std::string ex5 = "aa(((a)))";
    //ex5 = nomoreunusesparenthesis(ex5);
    std::cout << ex5 << " - " << nomoreunusesparenthesis(ex5) << std::endl;
    std::string ex6 = "((a)(((a)*)(a))*)*";
    //ex6 = nomoreunusesparenthesis(ex6);
    std::cout << ex6 << " - " << nomoreunusesparenthesis(ex6) << std::endl;
    std::string ex7 = "(a)*((a)a)*(a)";
    //ex7 = nomoreunusesparenthesis(ex7);
    std::cout << ex7 << " - " << nomoreunusesparenthesis(ex7) << std::endl;
}

void isfinaltest() {
    std::cout << "Is final? empty " << is_node_final("") << std::endl;
    std::cout << "Is final? a " << is_node_final("a") << std::endl;
    std::cout << "Is final? a* " << is_node_final("a*") << std::endl;
    std::cout << "Is final? ab " << is_node_final("ab") << std::endl;
    std::cout << "Is final? ab* " << is_node_final("ab*") << std::endl;
    std::cout << "Is final? (b*c)* " << is_node_final("(b*c)*") << std::endl;
    std::cout << "Is final? a(b*c)* " << is_node_final("a(b*c)*") << std::endl;
    std::cout << "Is final? (b*c)*a " << is_node_final("(b*c)*a") << std::endl;
    std::cout << "Is final? a(b*c)*a " << is_node_final("a(b*c)*a") << std::endl;
}

void backedgeneededtest() {
    std::cout << "Is final? empty " << back_edge_needed("") << std::endl;
    std::cout << "Is final? a " << back_edge_needed("a") << std::endl;
    std::cout << "Is final? a* " << back_edge_needed("a*") << std::endl;
    std::cout << "Is final? ab " << back_edge_needed("ab") << std::endl;
    std::cout << "Is final? ab* " << back_edge_needed("ab*") << std::endl;
    std::cout << "Is final? (b*c)* " << back_edge_needed("(b*c)*") << std::endl;
    std::cout << "Is final? a(b*c)* " << back_edge_needed("a(b*c)*") << std::endl;
    std::cout << "Is final? (b*c)*a " << back_edge_needed("(b*c)*a") << std::endl;
    std::cout << "Is final? a(b*c)*a " << back_edge_needed("a(b*c)*a") << std::endl;
}

void test_inner_expression() {
    StateMachine sm = buildStateMachine("a(b(da)*)*");
    std::string s1 = "a";
    std::cout << s1 << " exptected: 1, actual: " << sm.check(s1) << std::endl;
    std::string s2 = "ab";
    std::cout << s2 << " exptected: 1, actual: " << sm.check(s2) << std::endl;
    std::string s3 = "abda";
    std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;
    std::string s4 = "abbbbbbbb";
    std::cout << s4 << " exptected: 1, actual: " << sm.check(s4) << std::endl;
    std::string s5 = "abbbbbbbbda";
    std::cout << s5 << " exptected: 1, actual: " << sm.check(s5) << std::endl;
    std::string s6 = "abdadadada";
    std::cout << s6 << " exptected: 1, actual: " << sm.check(s6) << std::endl;
    std::string s7 = "abbdadabda";
    std::cout << s7 << " exptected: 1, actual: " << sm.check(s7) << std::endl;

    std::string s8 = "bbdadabda";
    std::cout << s8 << " exptected: 0, actual: " << sm.check(s8) << std::endl;
    std::string s9 = "abdaa";
    std::cout << s9 << " exptected: 0, actual: " << sm.check(s9) << std::endl;
    std::string s10 = "abdd";
    std::cout << s10 << " exptected: 0, actual: " << sm.check(s10) << std::endl;
    std::string s11 = "ada";
    std::cout << s11 << " exptected: 0, actual: " << sm.check(s11) << std::endl;
}

void test_simple_inner_expression() {
    StateMachine sm = buildStateMachine("a(bd)*a");
    std::string s1 = "aa";
    std::cout << s1 << " exptected: 1, actual: " << sm.check(s1) << std::endl;
    std::string s2 = "abda";
    std::cout << s2 << " exptected: 1, actual: " << sm.check(s2) << std::endl;
    std::string s3 = "abdbdbdbdbda";
    std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;

    std::string s4 = "abd";
    std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
    std::string s5 = "aba";
    std::cout << s5 << " exptected: 0, actual: " << sm.check(s5) << std::endl;
    std::string s6 = "ada";
    std::cout << s6 << " exptected: 0, actual: " << sm.check(s6) << std::endl;
    std::string s7 = "aabda";
    std::cout << s7 << " exptected: 0, actual: " << sm.check(s7) << std::endl;
    std::string s8 = "adba";
    std::cout << s8 << " exptected: 0, actual: " << sm.check(s8) << std::endl;
    std::string s9 = "a";
    std::cout << s9 << " exptected: 0, actual: " << sm.check(s8) << std::endl;
}

void test_no_inner() {
    {
        std::string ex = "a*";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "aaaaaaaaaaaaaan";
        std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        std::cout << s3 << " exptected: 0, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "aaaaaaaaaaaaaan";
        std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "ab";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 0, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << sm.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << sm.check(s6) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "ab*";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 1, actual: " << sm.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << sm.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << sm.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 1, actual: " << sm.check(s8) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a*b";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 0, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << sm.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << sm.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << sm.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 0, actual: " << sm.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 1, actual: " << sm.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 0, actual: " << sm.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 1, actual: " << sm.check(s11) << std::endl;
        sm.print_statemachine();
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a*b*";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 1, actual: " << sm.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << sm.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << sm.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 1, actual: " << sm.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 1, actual: " << sm.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 1, actual: " << sm.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 1, actual: " << sm.check(s11) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a*b*c";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 0, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 0, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "abc";
        std::cout << s4 << " exptected: 1, actual: " << sm.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << sm.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << sm.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << sm.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 0, actual: " << sm.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 0, actual: " << sm.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 0, actual: " << sm.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 0, actual: " << sm.check(s11) << std::endl;
        std::string s12 = "aaaaaaaaaaaaaaaaaaaaaaaaabcccccccccccccccccccc";
        std::cout << s12 << " exptected: 0, actual: " << sm.check(s12) << std::endl;
        std::string s13 = "c";
        std::cout << s13 << " exptected: 1, actual: " << sm.check(s13) << std::endl;
        std::string s14 = "cb";
        std::cout << s14 << " exptected: 0, actual: " << sm.check(s14) << std::endl;
        std::string s15 = "bc";
        std::cout << s15 << " exptected: 1, actual: " << sm.check(s15) << std::endl;
        std::string s16 = "ac";
        std::cout << s16 << " exptected: 1, actual: " << sm.check(s16) << std::endl;
        std::string s17 = "aaaaaaaaaaaaaaaaaaaaaaaaabc";
        std::cout << s17 << " exptected: 1, actual: " << sm.check(s17) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a*b*c*";
        StateMachine sm = buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << sm.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << sm.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << sm.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << sm.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 1, actual: " << sm.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << sm.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << sm.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 1, actual: " << sm.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 1, actual: " << sm.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 1, actual: " << sm.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 1, actual: " << sm.check(s11) << std::endl;
        std::string s12 = "aaaaaaaaaaaaaaaaaaaaaaaaabcccccccccccccccccccc";
        std::cout << s12 << " exptected: 1, actual: " << sm.check(s12) << std::endl;
        std::string s13 = "c";
        std::cout << s13 << " exptected: 1, actual: " << sm.check(s13) << std::endl;
        std::string s14 = "cb";
        std::cout << s14 << " exptected: 0, actual: " << sm.check(s14) << std::endl;
        std::string s15 = "bc";
        std::cout << s15 << " exptected: 1, actual: " << sm.check(s15) << std::endl;
        std::string s16 = "ac";
        std::cout << s16 << " exptected: 1, actual: " << sm.check(s16) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}

int main()
{
    /*
    std::map<int, int> asd;
    asd[1] = 21;
    asd[2] = 32;
    auto sear = asd.find(3);
    if (sear != asd.end()) {
        std::cout << "found " << sear->first << " " << sear->second << std::endl;
    }
    else {
        std::cout << "not found" << std::endl;
    }
    */
    //std::string cica = "cica";
    //std::cout << "subcica: " << cica.substr(cica.length(), 1);
    /*
    test_nomoreunusedparenthesis();
    isfinaltest();
    backedgeneededtest();
    */
    //test_inner_expression();
    //test_simple_inner_expression();
    test_no_inner();
    //test3();

    //std::cout << get_end_of_scope("aa(bc(bd))", 5) << std::endl;

    //StateMachine sm = buildStateMachine("a*b*a*");
    //StateMachine sm = buildStateMachine("a*b");

    /*
    std::string user_input;
    std::cin >> user_input;

    while (user_input != "exit") {
        if (user_input == "p") {
            sm.print_statemachine();
        }
        else {
            bool result = sm.check(user_input);
            std::cout << user_input << " is " << result << std::endl;
        }
        std::cin >> user_input;
    }
    */
    return 0;
}
