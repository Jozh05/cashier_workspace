#pragma once
#include <unordered_map>
#include <memory>
#include <json/json.h>
#include <fstream>
#include "Item.hpp"

class Catalog {
private:
    std::unordered_map<uint64_t, std::shared_ptr<Item>> itemsById;
    std::unordered_map<std::string, std::shared_ptr<Item>> itemsByName;

public: 
    void load(const std::string& filePath);
    std::shared_ptr<Item> find(uint64_t id) const;
    std::shared_ptr<Item> find(const std::string& name) const;
};