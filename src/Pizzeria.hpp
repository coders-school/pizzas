#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <chrono>
#include <memory>
#include "Timer.hpp"
#include "Pizza.hpp"

enum class Status
{
    New,
    Paid,
    Baked,
    Completed
};

using Order = std::tuple<int, Pizzas, std::chrono::system_clock::time_point, Status>;

class Pizzeria
{
public:
    Pizzeria(std::string const & name, std::unique_ptr<ITimer> timer);
    Pizzeria(std::string const & name, Timer& timer);
    int makeOrder(Pizzas pizzas);
    double calculatePrice(int orderId);
    void bakePizzas(int orderId);
    void completeOrder(int orderId);

private:
    std::string name_;
    std::vector<Order> orders_;
    std::unique_ptr<ITimer> timer_ptr = nullptr;
    Timer timer_;
};

