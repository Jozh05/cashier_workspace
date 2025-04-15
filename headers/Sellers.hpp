#pragma once
#include <string>
#include <unordered_map>

struct Seller {
    const std::string login;
    const std::string name;
    const std::string password;
    Seller(const std::string& login, const std::string& name, const std::string& password) : 
        login(login), name(name), password(password){}
};

extern std::ostream& operator << (std::ostream& os, const Seller& seller);

class Sellers {

private:
    std::unordered_map<std::string, Seller> workers;

public:
    void load(const std::string& filePath);
    const Seller* const find(const std::string& login) const;
};