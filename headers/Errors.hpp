#pragma once
#include <stdexcept>

class CriticalError : public std::runtime_error {
    public:
    explicit CriticalError(const std::string& message)
        : std::runtime_error(message) {}
};

class PaymentError : public std::runtime_error {
    public:
    explicit PaymentError(const std::string& message) 
        : std::runtime_error(message) {}
};