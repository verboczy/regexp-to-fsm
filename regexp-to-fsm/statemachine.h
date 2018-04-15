#ifndef STATEMACHINE_H_INCLUDED
#define STATEMACHINE_H_INCLUDED

#include <map>

#include "edge.h"

class StateMachine {
public:

    StateMachine();

    StateMachine(StateMachine const& other);
    StateMachine& operator=(StateMachine const& rhs);

    StateMachine(StateMachine && other) noexcept;
    StateMachine& operator=(StateMachine && rhs) noexcept;

    ~StateMachine();

    void add_state(Node node, std::list<Edge> edges);

    bool check(std::string expression);

private:
    std::map<Node, std::list<Edge>> states;
};

#endif
