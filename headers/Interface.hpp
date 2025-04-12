#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "Catalog.hpp"

class Interface {

public:

    Interface() = delete;

    static void printHello();
    static void printOrderInstructions();
    static void printMainMenu();
    static std::vector<std::string> parseCommand(const std::string& commandLine);
    static unsigned int validateQuantity(const std::string& token);
};