#include "../headers/Item.hpp"

std::ostream& operator << (std::ostream& stream, const Item& item){
    stream << "Barcode: " << item.id << " Name: " << item.name << " Price: " << item.price;
    return stream;
}