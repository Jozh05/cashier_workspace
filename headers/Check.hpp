#pragma once
#include "Catalog.hpp"

#include <vector>
#include <unordered_map>

enum class PaymentType {
    Cash, 
    NonCash
};


class Check {

friend class WorkShift;
private:    
    PaymentType paymentType = PaymentType::NonCash;
    std::unordered_map<uint64_t, unsigned int> items;
    const Catalog& catalog;
    
    Check(const Catalog& catalog) : 
        catalog(catalog){};

public:    
    Check() = delete;

    void add(uint64_t id, unsigned int count = 1);
    void add(const std::string& name, unsigned int count = 1);

    void remove(uint64_t id, unsigned int count = 1);
    void remove(const std::string& name, unsigned int count = 1);

};