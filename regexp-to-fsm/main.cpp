#include <iostream>

#include "statemachine.h"
#include "node.h"

using namespace std;

int main()
{
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

    return 0;
}
