#include "../headers/Item.hpp"

void Item::print() const {
    std::cout << "ID: " << this->id << " Name: " << 
        this->name << " Price: " <<  this->price << std::endl;
}