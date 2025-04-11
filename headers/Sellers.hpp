#pragma once
#include <string>
#include <unordered_map>

struct Seller {
    const std::string login;
    const std::string name;
    Seller(const std::string& login, const std::string& name) : 
        login(login), name(name){}
};

class Sellers {

private:
    std::unordered_map<std::string, Seller> workers;

public:
    void load(const std::string& filePath);
    const Seller* find(const std::string& login) const;
};