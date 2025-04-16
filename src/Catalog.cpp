#include "../headers/Catalog.hpp"
#include "../headers/Errors.hpp"

void Catalog::load(const std::string& filePath) {
    
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open()) {
        throw CriticalError("Failed to open catalog file");
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    
    if (bool ok = Json::parseFromStream(builder, file, &root, &errs); !ok) {
        throw CriticalError("Failed to parse catalog file");
    }

    file.close();

    for (const auto& item : root) {

        uint64_t id = item["id"].asUInt64();
        std::string name = item["name"].asString();
        double price = item["price"].asDouble();

        auto object = std::make_shared<Item>(id, name, price);

        itemsById[id] = object;
        itemsByName[name] = object;
    }
}

std::shared_ptr<Item> Catalog::find(uint64_t id) const {
    if (itemsById.contains(id))
        return itemsById.at(id);
    else
        return nullptr;
}

std::shared_ptr<Item> Catalog::find(const std::string& name) const {
    if (itemsByName.contains(name))
        return itemsByName.at(name);
    else
        return nullptr;
}