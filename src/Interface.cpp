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
        
        To complete the order formation type "end")" << std::endl;
}


void Interface::printStartMenu() {
    std::cout << R"(Please, select the action:
        1. Sign in
        2. Quit the program)" << std::endl;
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
    } catch (...) {
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

void Interface::printPaymentInstructions() {
    std::cout << "Please, choose a payment type." << std::endl;
    std::cout << R"(
    1. Cash
    2. Non-cash
    3. Cancel the order
    )" << std::endl;
}


double Interface::paymentInterface(PaymentType paymentType) {
    while (true) {
        std::cin.clear();
        std::cout << R"(To change payment type, please type "change")" << std::endl;
        if (paymentType == PaymentType::Cash) {
            std::cout << "Enter the payment amount: " << std::endl;
        }
        else {
            std::cout << "Enter the amount of money in the bank account: " << std::endl;
        }

        std::string pay; std::cin >> pay;
        if (pay == "change") {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return -1;
        }

        try {
            double result = std::stod(pay);
            if (paymentType == PaymentType::Cash && result < 0) {
                std::cout << "Incorrect amount" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return result;
        } catch (...) {
            std::cout << "Incorrect amount" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int Interface::validateMenu() {
    int result;
    while (true) {
        if (std::cin >> result && (result == 1 || result == 2)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return result;
        }
        else {
            std::cin.clear();
            std::cout << "Incorrect command." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int Interface::validatePaymentType() {
    int result;
    while (true) {
        if (std::cin >> result && (result == 1 || result == 2 || result == 3)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return result;
        }
        else {
            std::cin.clear();
            std::cout << "Incorrect command." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}