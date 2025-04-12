#include "../headers/Sellers.hpp"
#include <json/json.h>
#include <iostream>
#include <fstream>
#include "../headers/Errors.hpp"

std::ostream& operator<< (std::ostream& os, const Seller& seller) {
    os << seller.name;
    return os;
}

void Sellers::load(const std::string& filePath) {
    
    std::ifstream file(filePath, std::ifstream::binary);

    if (!file.is_open()) {
        throw CriticalError("Failed to open sellers file");
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (bool ok = Json::parseFromStream(builder, file, &root, &errs); !ok) {
        throw CriticalError("Failed to parse sellers file");
    }

    file.close();

    for (const auto& item : root) {
        std::string login = item["login"].asString();
        std::string name = item["name"].asString();
        workers.emplace(login, Seller(login, name));
    }
}

const Seller* const Sellers::find(const std::string& login) const {
    
    if (auto iter = workers.find(login); iter != workers.end())
        return &iter->second;
    else
        return nullptr;
}