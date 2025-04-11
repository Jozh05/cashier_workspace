#include "../headers/Item.hpp"

void Item::print() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "ID: " << this->id << " Name: " << 
        this->name << " Price: " <<  this->price << std::endl;
}