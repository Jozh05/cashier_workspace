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
            break;
        }
        case PaymentType::NonCash:
            nonCashPayment += sum;
            return 0;
            break;
        default:
            break;
        }
    }
}