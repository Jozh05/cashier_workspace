#include "../headers/Check.hpp"

void Check::add(uint64_t id, unsigned int count) {
    items[id] += count;
}

void Check::add(const std::string& name, unsigned int count) {
    uint64_t id = catalog.find(name)->id;
    add(id, count);
}


void Check::remove(uint64_t id, unsigned int count) {
    if (count > items[id])
        items.erase(id);
    else 
        items[id] -= count;
}


void Check::remove(const std::string& name, unsigned int count) {
    uint64_t id = catalog.find(name)->id;
    if (count > items[id])
        items.erase(id);
    else 
        items[id] -= count;
}


