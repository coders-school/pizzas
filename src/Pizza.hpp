#pragma once
#include <chrono>
#include <memory>
#include <set>
#include <string>

using minutes = std::chrono::seconds;  // To simulate time flow ;)

class Pizza {
public:
    Pizza(std::string const& name, double price, minutes bakingTime);
    virtual ~Pizza() = default;
    virtual std::string getName() const;
    virtual double getPrice() const;
    virtual minutes getBakingTime() const;

private:
    std::string name_;
    double price_;
    minutes bakingTime_;
};

// unique_ptr would require complex changes therefore I have choosen shared_ptr
using Pizzas = std::set<std::shared_ptr<Pizza>>;
