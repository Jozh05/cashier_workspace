#pragma once
#include "WorkShift.hpp"
#include "Sellers.hpp"
#include "Config.hpp"
#include "Errors.hpp"
#include "Interface.hpp"


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
    std::pair<std::string&, bool> validateProduct(std::string& product) const;

// Методы для взаимодействия с пользователем
private:
    void authentication();
    void MainMenu();
    void createOrder();
    void completeOrder();

public:
    void start();
    void stop(int returnCode);
};