#pragma once
#include "WorkShift.hpp"
#include "Sellers.hpp"

class App {

private:
    WorkShift workShift;
    Catalog catalog;
    Sellers sellersList;
    
private:
    void loadCatalog(const std::string& filePath);
    void loadSellersList(const std::string& filePath);
    void login();
    void endShift();

public:
    void start();
    int stop();
};