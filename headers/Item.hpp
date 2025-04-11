#pragma once
#include <string>
#include <iostream>
#include <iomanip>

struct Item {
    const uint64_t id;
    const std::string name;
    const double price;
    
    Item(uint64_t id, const std::string& name, double price) :
        id(id), name(name), price(price){}

    void print() const;
};