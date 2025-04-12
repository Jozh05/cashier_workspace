#pragma once
#include <string>
#include "Check.hpp"
#include "Sellers.hpp"

class WorkShift {

    friend class App;
private:
    const std::string sellerLogin; // Login кассира
    double cash = 10000; // Количество наличных денег
    double cashPayment = 0; // Оплачено наличными
    double nonCashPayment = 0; // Оплачено безналом
    Check check;

    WorkShift (const std::string& sellerLogin, const Catalog& catalog, const Seller& seller) :
        sellerLogin(sellerLogin), check(Check(catalog)), seller(seller) {}

public:
    const Seller& seller;

public:
    ~WorkShift() = default;

    void startOrder();
    double endOrder();

    double payment(double sum, double pay, PaymentType);
};