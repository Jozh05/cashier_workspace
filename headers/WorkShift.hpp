#pragma once
#include <string>
#include "Check.hpp"
#include "Sellers.hpp"

class WorkShift {

    friend class App;
private:
    
    double cash = 10000; // Количество наличных денег
    double cashPayment = 0; // Оплачено наличными
    double nonCashPayment = 0; // Оплачено безналом
    Check check;
    const Seller& seller;

    WorkShift (const Catalog& catalog, const Seller& seller) :
         check(Check(catalog)), seller(seller) {}

public:
    ~WorkShift() = default;

    void startOrder();
    double endOrder();

    double payment(double sum, double pay, PaymentType);
};