#pragma once
#include "WorkShift.hpp"
#include "Sellers.hpp"
#include "Config.hpp"
#include "Errors.hpp"
#include <sstream>
#include <vector>

class App {

private:
    WorkShift* workShift = nullptr;
    Catalog catalog;
    Sellers sellersList;
    
private:
    void loadCatalog(const std::string& filePath);
    void loadSellersList(const std::string& filePath);
    bool signIn(const std::string& login);
    void endShift();

// Методы для взаимодействия с пользователем
private:
    void interfaceAuth();
    void interfaceMainMenu();
    void createOrder();
    void completeOrder();
    

// Вспомогательные методы
private:
    void printHello() const;
    void printOrderInstructions() const;
    std::pair<std::string&, bool> validateProduct(std::string& product) const;
    std::vector<std::string> parseCommand(const std::string& commandLine) const;
    unsigned int validateQuantity(const std::string& token) const;
    

public:
    void start();
    void stop(int returnCode);
};