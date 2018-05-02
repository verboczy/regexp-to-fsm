#ifndef STATEMACHINE_H_INCLUDED
#define STATEMACHINE_H_INCLUDED

#include <map>
#include <unordered_set>

#include "edge.h"

extern char epsilon;

class StateMachine {
public:
    void add_state(Node node, std::list<Edge> edges);

    bool check(std::string expression) const;

    void add_edge_to_list(Node node, Edge edge);

    bool contains_node(Node node);

private:
    std::map<Node, std::list<Edge>> states;

    Node get_initial() const;
};

class StateMachineBuilder {
public:

    void buildStateMachine(std::string expression);

    bool check(std::string expression);
private:
    std::list<StateMachine> statemachine_list;

    size_t get_end_of_scope(std::string str, size_t startposition);

    size_t get_start_of_scope(std::string str, size_t startposition);

    std::string plustostar(std::string expression);

    std::unordered_set<std::string> nomoreor(std::string expression, std::unordered_set<std::string> withoutor);

    bool is_node_final(std::string expression);

    std::string nomoreunusesparenthesis(std::string expression);

    std::list<Node> buildSubStateMachine(StateMachine& sm, std::string expression, std::list<Node> initial_node_list,
                                            std::list<Node>& original_node_list, bool is_it_final);

    StateMachine buildSingleStateMachine(std::string expression);
};

#endif
