#include "../headers/App.hpp"

void App::loadCatalog(const std::string& filePath) {
    catalog = Catalog();
    try {
        catalog.load(filePath);
    } catch (const CriticalError& err) {
        std::cerr << "Fatal error: " << err.what() << std::endl;
        stop(1);
    }
}

void App::loadSellersList(const std::string& filePath) {
    sellersList = Sellers();
    try {
        sellersList.load(filePath);
    } catch (const CriticalError& err) {
        std::cerr << "Fatal error: " << err.what() << std::endl;
        stop(2);
    }
}

bool App::signIn(const std::string& login) {
    if (auto seller = sellersList.find(login); seller != nullptr){
        workShift = new WorkShift(catalog, *seller);
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
        std::cin.clear();
        std::cout << "Enter your login:\t";
        std::cin >> login;
        if (!signIn(login))
            std::cout << "Incorrect login. Please try again." << std::endl;
        else
            isAuthenticated = true;

    } while (!isAuthenticated); 
}

std::pair<std::string&, bool> App::validateProduct(std::string& product) {
    try {
        uint64_t id = stoull(product);
        if (catalog.find(id) != nullptr)
            return {product, true};
        else {
            product = "";
            return {product, false};
        }
    } catch (const std::invalid_argument&) {
        if (catalog.find(product) != nullptr)
            return {product, false};
        else {
            product = "";
            return {product, false};
        }
    } catch (const std::out_of_range&) {
        product = "";
        return {product, false};
    }
}

void App::createOrder() {
    std::string command;
    std::string product;
    std::cout << R"(
        To add an item to an order type "add <Product name or id>"
        To remove an item from an order type "remove <Product name or id>"
        To complete the order formation type "end"
    )";
    while (true) {
        std::cin >> command;
        if (command == "end") {
            completeOrder();
            break;
        }
        std::cin >> product;
        auto validate = validateProduct(product);
        if (validate.first.empty())
            std::cout << "Incorrect product." << std::endl;

        else if (validate.second && command == "add") 
            workShift->check.add(std::stoull(validate.first));

        else if (validate.second && command == "remove")
            workShift->check.add(std::stoull(validate.first));

        else if (command == "add")
            workShift->check.add(validate.first);

        else if (command == "remove")
            workShift->check.remove(validate.first);
        
        else
            std::cout << "Incorrect command" << std::endl;
    } 
}

void App::completeOrder() {
    std::cout << "Complete!" << std::endl;
}

void App::interfaceMainMenu() {
    int command;
    while (true) {
        std::cin.clear();
        std::cout << "Shift is active. User login: " << workShift->seller.login << std::endl;
        std::cout << R"(   
        Select an action:

        1. Create new order
        2. Print the report and sign out

        )";
        std::cin >> command;

        switch (command)
        {
        case 1:
            createOrder();
            break;
        case 2:
            stop(0);
            break;
        default:
            break;
        }

    } while (command != 2);
}


void App::start() {

    loadCatalog(catalogPath);
    loadSellersList(sellersListPath);

    sayHello();

    interfaceAuth();

    interfaceMainMenu();

}

void App::stop(int returnCode) {
    if (workShift != nullptr)
        endShift();
    exit(returnCode);
}