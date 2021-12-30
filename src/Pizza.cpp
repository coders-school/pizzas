#include "Pizza.hpp"

Pizza::Pizza(std::string const& name, double price, minutes bakingTime)
    : name_(name), price_(price), bakingTime_(bakingTime) {}

std::string Pizza::getName() const {
    return name_;
}

double Pizza::getPrice() const {
    return 30.0;
}

minutes Pizza::getBakingTime() const {
    return bakingTime_;
}
