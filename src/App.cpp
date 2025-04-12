#include "../headers/App.hpp"

void App::loadCatalog(const std::string& filePath) {
    catalog = Catalog();
    catalog.load(filePath);
}

void App::loadSellersList(const std::string& filePath) {
    sellersList = Sellers();
    sellersList.load(filePath);
}

bool App::signIn(const std::string& login) {
    if (auto seller = sellersList.find(login); seller != nullptr){
        workShift = new WorkShift(login, catalog, *seller);
    }
    else{
        return false;
    }
    return true;
}

void App::endShift() {
    delete workShift;
    workShift = nullptr;
}

void App::sayHello() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << R"(
        ===========================================
               Welcome to the Cashier System
        ===========================================
        
        To begin your shift, please enter your login.
        Authorization is required to start working.
        )" << std::endl;
}

void App::interfaceAuth() {
    std::string login;
    bool isAuthenticated = false;
    do {
        std::cout << "Enter your login:\t";
        std::cin >> login;
        if (!signIn(login))
            std::cout << "Incorrect login. Please try again." << std::endl;
        else
            isAuthenticated = true;

    } while (!isAuthenticated); 
}


void App::interfaceMainMenu() {
    int comand;
    do {
        std::cout << R"(
            Select an action:

            1. Create new order
            2. Print the report and sign out
        )";
        std::cin >> comand;

        switch (comand)
        {
        case 1:
            workShift->startOrder();
            break;
        
        default:
            break;
        }

    } while (comand != 2);
}


void App::start() {

    loadCatalog(catalogPath);
    loadSellersList(sellersListPath);

    sayHello();

    interfaceAuth();

    interfaceMainMenu();

}

void App::stop(int returnCode) {
    endShift();
    exit(returnCode);
}