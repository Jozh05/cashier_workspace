#include "../headers/WorkShift.hpp"
#include "../headers/Errors.hpp"

double WorkShift::endOrder() {
    
    double result = 0;
    for (auto it = check.items.begin(); it != check.items.end(); it++) {
        result += check.catalog.find(it->first)->price * it->second;
    }
    return result;
}

void WorkShift::startOrder() {
    check.items.clear();
}

double WorkShift::payment(double sum, double pay, PaymentType paymentType) {
    
    if (pay < sum)
            throw PaymentError("Insufficient funds");
    else {
        switch (paymentType)
        {
        case PaymentType::Cash: {
            double change = pay - sum;
            cash += pay;
            cash -= change;
            cashPayment += sum;
            return change;
        }
        case PaymentType::NonCash:
            nonCashPayment += sum;
            return 0;
        default:
            return 0;
        }
    }
}

void WorkShift::printCheck() const{
    unsigned int total = 0;
    std::cout << "Check report:" << std::endl;
    std::cout << "Cashier's name: " << seller << std::endl;
    for (auto iter = check.items.begin(); iter != check.items.end(); iter++) {
        auto item = *check.catalog.find(iter->first);
        auto quantity = iter->second;
        std::cout << item << " Quantity: " << quantity << " Total price: " << item.price * quantity << std::endl;
        total += item.price * quantity;
    }
    std::cout << "TOTAL PRICE: " << total << std::endl;
}