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

void App::printHello() const {
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

unsigned int App::validateQuantity(const std::string& token) const {
    
    if (token.front() == '-')
        return 0;
    try {
        unsigned int quan = std::stoul(token);
        return quan;
    } catch (const std::invalid_argument&) {
        return 0;
    } catch (const std::out_of_range&) {
        return 0;
    }
}

std::vector<std::string> App::parseCommand(const std::string& commandLine) const {

        std::istringstream iss(commandLine);
        std::vector<std::string> tokens;
        tokens.reserve(3);
        std::string token;

        for (int i = 0; i != 3 && iss >> token; ++i) {
            tokens.push_back(token);
        }
        return tokens;
}

void App::printOrderInstructions() const {
    std::cout << R"(
        To add one item to an order, type "add <Product name or id>"
        To add <number> items to an order, type "add <Product name or id> <number>"

        To remove one item from an order, type "remove <Product name or id>"
        To remove <number> items from an order, type "remove <Product name or id> <number>"
        
        To complete the order formation type "end"
    )";
}

void App::createOrder() {
    std::cin.clear();
    std::cin.ignore();

    printOrderInstructions();

    std::string commandLine;
    
    while (true) {

        std::getline(std::cin, commandLine);
        if (commandLine.empty()) continue;

        std::cout << commandLine << std::endl;
        std::vector<std::string> tokens = std::move(parseCommand(commandLine));
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
            quantity = validateQuantity(tokens[2]);

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
    2. Print the report and sign out)";
        std::cout << std::endl;
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

    printHello();

    interfaceAuth();

    interfaceMainMenu();

}

void App::stop(int returnCode) {
    if (workShift != nullptr)
        endShift();
    exit(returnCode);
}