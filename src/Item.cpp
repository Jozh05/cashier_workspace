#include "../headers/Item.hpp"

std::ostream& Item::operator << (std::ostream& stream) const{
    stream << "Barcode: " << id << " Name: " << name << " Price: " << price;
    return stream;
}