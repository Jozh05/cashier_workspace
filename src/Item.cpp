#include "../headers/Item.hpp"

std::ostream& operator << (std::ostream& stream, const Item& item){
    stream << "Barcode: " << item.id << "\tName: " << item.name << "\tPrice: " << item.price;
    return stream;
}