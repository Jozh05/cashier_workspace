#pragma once
#include <string>
#include <stdexcept>
#include "Check.hpp"
#include "App.hpp"


class WorkShift {

    friend class App;
private:
    const std::string sellerLogin; // Login кассира
    double cash = 10000; // Количество наличных денег
    double cashPayment = 0; // Оплачено наличными
    double nonCashPayment = 0; // Оплачено безналом
    Check check;

    WorkShift (const std::string& sellerLogin, const Catalog& catalog) :
        check(Check(catalog)), sellerLogin(sellerLogin){}

public:
    ~WorkShift() = default;

    void startOrder();
    double endOrder();

    double payment(double sum, double pay, PaymentType);
};