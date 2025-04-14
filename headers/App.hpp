#pragma once
#include "WorkShift.hpp"
#include "Sellers.hpp"
#include "Config.hpp"
#include "Errors.hpp"
#include "Interface.hpp"
#include <csignal>


enum class AppState {
    StartMenu,
    MainMenu,
    OrderCreation,
    OrderComplition,
    Exit
};

class App {

private:
    WorkShift* workShift = nullptr;
    Catalog catalog;
    Sellers sellersList;

    AppState state = AppState::StartMenu;
    
private:
    void loadCatalog(const std::string& filePath);
    void loadSellersList(const std::string& filePath);
    bool signIn(const std::string& login);
    void endShift();
    std::pair<std::string&, bool> validateProduct(std::string& product) const;


private:
    bool authentication();
    void StartMenu();
    void MainMenu();
    void createOrder();
    void completeOrder();

public:
    void start();
    void stop(int returnCode);
};