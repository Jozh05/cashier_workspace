#include "../headers/Interface.hpp"

void Interface::printHello() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << R"(
        ===========================================
               Welcome to the Cashier System
        ===========================================
        
        To begin your shift, please enter your login.
        Authorization is required to start working.
        )" << std::endl;
}

void Interface::printOrderInstructions() {
    std::cout << R"(
        To add one item to an order, type "add <Product name or id>"
        To add <number> items to an order, type "add <Product name or id> <number>"

        To remove one item from an order, type "remove <Product name or id>"
        To remove <number> items from an order, type "remove <Product name or id> <number>"
        
        To complete the order formation type "end"
    )";
}


std::vector<std::string> Interface::parseCommand(const std::string& commandLine) {
    std::istringstream iss(commandLine);
        std::vector<std::string> tokens;
        tokens.reserve(3);
        std::string token;

        for (int i = 0; i != 3 && iss >> token; ++i) {
            tokens.push_back(token);
        }
        return tokens;
}

unsigned int Interface::validateQuantity(const std::string& token) {
    if (token.front() == '-')
        return 0;
    try {
        unsigned int quan = std::stoul(token);
        return quan;
    } catch (const std::invalid_argument&) {
        return 0;
    } catch (const std::out_of_range&) {
        return 0;
    }
}

void Interface::printMainMenu() {
        std::cout << R"(
    Select an action:

    1. Create new order
    2. Print the report and sign out)";
        std::cout << std::endl;
}