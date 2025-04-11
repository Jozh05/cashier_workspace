#include "../headers/App.hpp"

void App::loadCatalog(const std::string& filePath) {
    catalog = Catalog();
    catalog.load(filePath);
}

void App::loadSellersList(const std::string& filePath) {
    sellersList = Sellers();
    catalog.load(filePath);
}