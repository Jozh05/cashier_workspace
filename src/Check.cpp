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


/*
double Check::close(PaymentType paymentType, unsigned int pay) {
    double result = 0;
    this->paymentType = paymentType;

    for (auto it = items.begin(); it != items.end(); it++) {
        result += catalog.find(it->first)->price * it->second;
    }

    switch (paymentType)
    {
    case PaymentType::Cash:
        if (pay > result)
            workShift.cash += pay;
        break;
    case PaymentType::NonCash:
        
    default:
        break;
    }

    return result;
}
*/

