#pragma once
#include "Check.hpp"
#include "Sellers.hpp"

class WorkShift {

    friend class App;
private:
    
    double cash; // Количество наличных денег в кассе
    double cashPayment = 0; // Оплачено наличными
    double nonCashPayment = 0; // Оплачено безналом
    Check check;
    const Seller& seller;

    WorkShift (const Catalog& catalog, const Seller& seller, double cash = 10000) :
         check(Check(catalog)), seller(seller), cash(cash) {}

public:
    ~WorkShift() = default;

    void startOrder();
    double endOrder() const;

    double payment(double sum, double& pay, PaymentType);

    void printCheck(double sum, double pay, double change) const;

    void printReport() const;
};