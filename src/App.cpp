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


bool App::authentication() {
    std::string login;
    
    while (true) {
        std::cin.clear();
        std::cout << "Type \"back\" to return to start menu" << std::endl;
        std::cout << "Enter your login:\t";

        std::cin >> login;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (login == "back")
            return false;

        if (!signIn(login))
            std::cout << "Incorrect login. Please try again." << std::endl;
        else
            return true;
    }
}

void App::createOrder() {
    Interface::printOrderInstructions();
    workShift->startOrder();

    std::string commandLine;

    while (true) {
        std::cin.clear();
        std::getline(std::cin, commandLine);
        if (commandLine.empty()) continue;
        
        std::vector<std::string> tokens = std::move(Interface::parseCommand(commandLine));
        if (tokens[0] == "end") {
            state = AppState::OrderComplition;
            return;
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

    double sum = workShift->endOrder();
    
    while (true) {
        
        std::cout << "The amount of order: " << sum << std::endl;
        Interface::printPaymentInstructions();

        int command = Interface::validatePaymentType();

        PaymentType paymentType;
        double pay;
        double change;
        switch (command)
        {
        // Cash
        case 1: 
            paymentType = PaymentType::Cash;
            pay = Interface::paymentInterface(paymentType);
            break;
        // Non-cash
        case 2: 
            paymentType = PaymentType::NonCash;
            pay = Interface::paymentInterface(paymentType);
            break;
        // Cancel
        case 3:
            std::cout << "Order has been cancelled" << std::endl;
            state = AppState::MainMenu;
            return;
        default:
            std::cin.clear();
            std::cout << "Unknown command" << std::endl;
            return;
        }

        if (pay == -1)
            continue;
        
        try {
            change = workShift->payment(sum, pay, paymentType);
            workShift->printCheck(sum, pay, change);
            state = AppState::MainMenu;
            return;
        } catch (const PaymentError& err) {
            std::cout << err.what() << std::endl;
        }
    }   
}

void App::StartMenu() {
    
    while (true) {
        Interface::printHello();
        Interface::printStartMenu();
        int command = Interface::validateMenu();
    
        switch (command)
        {
        case 1:
            if (authentication()) {
                state = AppState::MainMenu;
                return;
            }
            else
                continue;
            break;
        case 2:
            state = AppState::Exit;
            return;
        default:
            break;
        }
    }
}

void App::MainMenu() {
    while (true) {
        std::cin.clear();
        std::cout << "Shift is active. User login: " << workShift->seller.login << std::endl;
        Interface::printMainMenu();
        
        int command = Interface::validateMenu();

        switch (command)
        {
        case 1:
            state = AppState::OrderCreation;
            return;
        case 2:
            workShift->printReport();
            state = AppState::StartMenu;
            return;
        default:
            break;
        }

    }
}


void App::start() {

    loadCatalog(catalogPath);
    loadSellersList(sellersListPath);

    while (state != AppState::Exit) {
        switch (state)
        {
        case AppState::StartMenu:
            StartMenu();
            break;
        case AppState::OrderCreation:
            createOrder();
            break;
        case AppState::OrderComplition:
            completeOrder();
            break;
        case AppState::MainMenu:
            MainMenu();
            break;
        case AppState::Exit:
            stop(0);
        default:
            break;
        }
    }
}

void App::stop(int returnCode) {
    if (workShift != nullptr)
        endShift();
    exit(returnCode);
}