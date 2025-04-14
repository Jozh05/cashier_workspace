#include "../headers/WorkShift.hpp"
#include "../headers/Errors.hpp"

double WorkShift::endOrder() const {
    
    double result = 0;
    for (auto it = check.items.begin(); it != check.items.end(); it++) {
        result += check.catalog.find(it->first)->price * it->second;
    }
    return result;
}

void WorkShift::startOrder() {
    check.items.clear();
}

double WorkShift::payment(double sum, double& pay, PaymentType paymentType) {
    
    if (pay < sum)
            throw PaymentError("Insufficient funds");
    else {
        switch (paymentType)
        {
        case PaymentType::Cash: { 
            pay = (pay > sum + 5000) ? sum + 5000 : pay;
            double change = pay - sum;
            if (change > cash)
                throw PaymentError("There is no change for that amount");
            cash += sum;
            cashPayment += sum;
            check.paymentType = PaymentType::Cash;
            return change;
        }
        case PaymentType::NonCash:
            nonCashPayment += sum;
            pay = sum;
            check.paymentType = PaymentType::NonCash;
            return 0;
        default:
            return 0;
        }
    }
}

void WorkShift::printCheck(double total, double pay, double change) const {
    std::cout << "Check report:" << std::endl;
    std::cout << "Cashier's name: " << seller << std::endl;
    for (auto iter = check.items.begin(); iter != check.items.end(); iter++) {
        auto item = *check.catalog.find(iter->first);
        auto quantity = iter->second;
        std::cout << item << "\tQuantity: " << quantity << "\tFinal price: " << item.price * quantity << std::endl;
    }
    std::cout << "TOTAL PRICE: " << total << std::endl;
    
    std::cout << "Payment type: ";
    if (check.paymentType == PaymentType::Cash)
        std::cout << "Cash" << std::endl;
    else if (check.paymentType == PaymentType::NonCash)
        std::cout << "Non-cash" << std::endl;

    std::cout << "Payment amount: " << pay << std::endl;
    std::cout << "Change: " << change << "\n\n";
}

void WorkShift::printReport() const {
    std::cout << "The shift is over. User login: " << seller.login << std::endl;
    std::cout << "Paid in cash: " << cashPayment << std::endl;
    std::cout << "Paid by bank transfer: " << nonCashPayment << std::endl;
    std::cout << "Total revenue per shift: " << cashPayment + nonCashPayment << std::endl;
}