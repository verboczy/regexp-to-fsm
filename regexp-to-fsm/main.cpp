#include <iostream>

#include "statemachine.h"

using namespace std;

int main()
{
    StateMachineBuilder smb;
    std::string user_statemachine;
    bool valid_input = false;
    while (!valid_input) {

    std::cin >> user_statemachine;
        try {
            smb.buildStateMachine(user_statemachine);
            valid_input = true;
        } catch (std::invalid_argument) {
            std::cout << "Please check the expression and try again!" << std::endl;
        }
    }

    std::string user_input;
    std::cin >> user_input;
    while (user_input != "exit") {
        bool result;
        try {
            result = smb.check(user_input);
        } catch(std::invalid_argument) {
            std::cout << "Something went wrong please try again!" << std::endl;
            return 1;
        }
        std::cout << user_input << " is " << result << std::endl;
        std::cin >> user_input;
    }

    return 0;
}
