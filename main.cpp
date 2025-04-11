#include <iostream>
#include "./headers/Catalog.hpp"
#include "./headers/Check.hpp"

int main() {
    Catalog catalog;
    catalog.load();
    catalog.find("Milk")->print();
    catalog.find(4837261940)->print();

    
    check.add("Milk");
    check.add(4837261940, 2);

    return 0;
}