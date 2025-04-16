#pragma once

#include <sstream>
#include <iomanip>
#include <limits>
#include "Check.hpp"

class Interface {

public:

    Interface() = delete;

    static void printHello();
    static void printStartMenu();
    static void printOrderInstructions();
    static void printMainMenu();
    static void printPaymentInstructions();

    static std::vector<std::string> parseCommand(const std::string& commandLine);
    static unsigned int validateQuantity(const std::string& token);
    static double paymentInterface(PaymentType);
    static int validateMenu();
    static int validatePaymentType();
};