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


void App::authentication() {
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

void App::createOrder() {
    std::cin.clear();
    std::cin.ignore();

    Interface::printOrderInstructions();
    workShift->startOrder();

    std::string commandLine;

    while (true) {
        std::cin.clear();
        std::getline(std::cin, commandLine);
        if (commandLine.empty()) continue;
        
        std::vector<std::string> tokens = std::move(Interface::parseCommand(commandLine));
        if (tokens[0] == "end") {
            completeOrder();
            break;
        }
        else if (tokens[0] != "remove" && tokens[0] != "add" || tokens.size() < 2) {
            std::cout << "Incorrect command" << std::endl;
            continue;
        }
    
        auto valid = validateProduct(tokens[1]);
        
        unsigned int quantity = 1;
        if (tokens.size() == 3)
            quantity = Interface::validateQuantity(tokens[2]);

        if (quantity == 0) {
            std::cout << "Incorrect quantity. Changed to the default value = 1" << std::endl;
            quantity = 1;
        }

        if (valid.first.empty()) {
            std::cout << "Incorrect product" << std::endl;
        }
        else if (valid.second && tokens[0] == "add") {
            workShift->check.add(std::stoull(tokens[1]), quantity);
        }
        else if (valid.second && tokens[0] == "remove"){
            workShift->check.remove(std::stoull(tokens[1]), quantity);
        }
        else if (tokens[0] == "add") {
            workShift->check.add(valid.first, quantity);
        }
        else if (tokens[0] == "remove") {
            workShift->check.remove(valid.first, quantity);
        }
    }
}

std::pair<std::string&, bool> App::validateProduct(std::string& product) const {
    try {
        uint64_t id = stoull(product);
        if (catalog.find(id) != nullptr)
            return {product, true};
        else {
            product.clear();
            return {product, false};
        }
    } catch (const std::invalid_argument&) {
        if (catalog.find(product) != nullptr)
            return {product, false};
        else {
            product.clear();
            return {product, false};
        }
    } catch (const std::out_of_range&) {
        product.clear();
        return {product, false};
    }
}

void App::completeOrder() {
    workShift->printCheck();
    std::cout << "Complete!" << std::endl;
}

void App::MainMenu() {
    int command;
    while (true) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Shift is active. User login: " << workShift->seller.login << std::endl;
        Interface::printMainMenu();
        
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

    }
}


void App::start() {

    loadCatalog(catalogPath);
    loadSellersList(sellersListPath);

    Interface::printHello();

    authentication();

    MainMenu();

}

void App::stop(int returnCode) {
    if (workShift != nullptr)
        endShift();
    exit(returnCode);
}