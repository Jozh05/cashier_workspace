#include "../headers/Sellers.hpp"
#include <json/json.h>
#include <iostream>
#include <fstream>

void Sellers::load(const std::string& filePath) {
    
    std::ifstream file(filePath, std::ifstream::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open sellers file");
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (bool ok = Json::parseFromStream(builder, file, &root, &errs); !ok) {
        throw std::runtime_error("Failed to parse sellers file");
    }

    file.close();

    for (const auto& item : root) {
        std::string login = item["login"].asString();
        std::string name = item["name"].asString();
        workers.emplace(login, Seller(login, name));
    }
}