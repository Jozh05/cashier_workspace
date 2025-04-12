#pragma once
#include "WorkShift.hpp"
#include "Sellers.hpp"
#include "Config.hpp"

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


private:
    void sayHello();
    void interfaceAuth();
    void interfaceMainMenu();

public:
    void start();
    void stop(int returnCode);
};